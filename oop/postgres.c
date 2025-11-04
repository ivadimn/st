#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

/* for ntohl/htonl */
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../lib/src/log.h"
#include "../lib/src/vstrex.h"
#include "../lib/src/array.h"
#include "postgres.h"
#include "row.h"

#define PARAN_NUM_LEN   4

static PGresult* __param_select(conn_t* conn, char *sql, param_list_t* params, size_t pcount)
{
    PGresult *res;
    size_t i = 0;
    const char* param_values[pcount];
    char param_num[PARAN_NUM_LEN];
    char param_sql[MAX_SQL_LEN];
    vstr_t *where = vstr_create(MAX_SQL_LEN);
    vstr_assign(where, " WHERE ");
    for (; i < pcount - 1; i++)
    {
        snprintf(param_num, PARAN_NUM_LEN - 1, "%ld", i + 1);
        vstr_plusv(where, 5, params->params[i].name, params->params[i].op, "$", param_num, " AND " );
    }
    snprintf(param_num, PARAN_NUM_LEN - 1, "%ld", i + 1);
    vstr_plusv(where, 5, params->params[i].name, params->params[i].op, "$", param_num, "; " );
    
    for (size_t i = 0; i < pcount; i++)
    {
        param_values[i] = params->params[i].text_value;
    }
    snprintf(param_sql, MAX_SQL_LEN - 1, "%s %s", sql, vstr_get_data(where));

    
    res = PQexecParams(conn->db,
                       param_sql,
                       pcount,       
                       NULL,        /* пусть бэкэнд выведет тип параметра */
                       param_values,
                       NULL,        /* не нужны длины параметров, так как текст */
                       NULL,        /* по умолчанию для всех текстовых параметров */
                       0);          /* запросить текстовые результаты */

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        snprintf(conn->error_message, ERR_MSG_LEN - 1, "Ошибка выполнения запроса: %s", PQerrorMessage(conn->db));
        err(conn->error_message);
        return NULL;
    }
    vstr_free(where);
    return res;
}


static PGresult* __simple_select(conn_t *conn, const char* sql)
{
    PGresult *res;
    res = PQexec(conn->db, sql);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        snprintf(conn->error_message, ERR_MSG_LEN - 1, "Ошибка выполнения запроса: %s", PQerrorMessage(conn->db));
        err(conn->error_message);
        return NULL;
    }
    return res;
}

// Функция для обмена байтов (если ваша система использует little-endian)
double swap_double_bytes(const char *data)
{
    union {
        double d;
        char c[sizeof(double)];
    } in, out;

    memcpy(in.c, data, sizeof(double));

    for (size_t i = 0; i < sizeof(double); ++i) {
        out.c[i] = in.c[sizeof(double) - 1 - i];
    }

    return out.d;
}

void
exit_nicely(PGconn *conn)
{
    PQfinish(conn);
    exit(1);
}


/* Эта функция выводит результат запроса в двоичном формате из
* таблицы, определённой в комментарии выше. Мы разделяем его, поскольку
* функция main() использует его дважды.
*/

void
show_binary_results(PGresult *res)
{
    int         i,
                j;
    int         i_fnum,
                t_fnum,
                b_fnum,
                d_fnum;

    /* Возвращает номер столбца, соответствующий данному имени столбца. */
    /* Используйте PQfnumber, чтобы избежать предположений о порядке полей в результате. */
    i_fnum = PQfnumber(res, "i");
    t_fnum = PQfnumber(res, "t");
    b_fnum = PQfnumber(res, "b");
    d_fnum = PQfnumber(res, "salary");

    for (i = 0; i < PQntuples(res); i++)
    {
        char       *iptr;
        char       *tptr;
        char       *bptr;
        char       *dptr;
        int         blen;
        int         ival;
        double      dval;

        /* Получить значения полей (мы игнорируем возможность того, что они равны NULL!) */
        iptr = PQgetvalue(res, i, i_fnum);
        tptr = PQgetvalue(res, i, t_fnum);
        bptr = PQgetvalue(res, i, b_fnum);
        dptr = PQgetvalue(res, i, d_fnum);

        /*
        * Двоичное представление INT4 имеет сетевой порядок байтов, который
        * лучше привести к локальному порядку байтов. */
        ival = ntohl(*((uint32_t *) iptr));
        // Если ваша архитектура не big-endian, обмениваем байты
            #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
                dval = swap_double_bytes(dptr);
            #else
                memcpy(&value, raw_data, sizeof(double));
            #endif

        /*
        * Двоичное представление TEXT — это, по сути, текст, и поскольку libpq
        * была настолько любезна, что добавила к нему нулевой байт, он будет прекрасно работать
        * как строка C.
        *
        * Двоичное представление BYTEA — это набор байтов, который может
        * включать в себя встроенные нули, поэтому необходимо обращать внимание на длину поля.
        */
        blen = PQgetlength(res, i, b_fnum);

        printf("tuple %d: got\n", i);
        printf(" i = (%d bytes) %d\n",
               PQgetlength(res, i, i_fnum), ival);
        printf(" t = (%d bytes) '%s'\n",
               PQgetlength(res, i, t_fnum), tptr);
        printf(" b = (%d bytes) ", blen);
        for (j = 0; j < blen; j++)
            printf("\\%02x", bptr[j]);
        printf("\n");    
        printf(" salary = (%d bytes) %f\n",
               PQgetlength(res, i, d_fnum), dval);
        printf("\n\n");
    }
}

PGresult* do_select(conn_t* conn, char *sql, param_list_t* params, size_t pcount)
{
    if (pcount == 0)
        return __simple_select(conn, sql);
    else
        return __param_select(conn, sql, params, pcount);    
}

int do_insert(conn_t* conn, char *sql, array_t* arr, size_t pcount, size_t row_count)
{
    PGresult *res;
    char* stmt_name = "insert_data";
    const char* param_values[pcount];
    vstr_array_t *current;
    vstr_t* str;
    res = PQprepare(conn->db, stmt_name, sql, pcount, NULL); 

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
         snprintf(conn->error_message, ERR_MSG_LEN - 1, 
                    "Ошибка подготовки команды INSERT: %s", PQerrorMessage(conn->db));
         err(conn->error_message);
         PQclear(res);
         return 1;
    }

    for (size_t i = 0; i < row_count; i++)
    {
        get(arr, i, &current);
        for (size_t j = 0; j < pcount; j++)
        {
            str = vstr_array_get(current, j);
            param_values[j] = vstr_get_data(str);
        }
         res = PQexecPrepared(conn->db, stmt_name, pcount, param_values, NULL, NULL, 0);

         if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            snprintf(conn->error_message, ERR_MSG_LEN - 1, 
                "Ошибка команды INSERT: %s", PQerrorMessage(conn->db));
            err(conn->error_message);
            PQclear(res);
            return 1;
         }
         
    }
    printf("inserted\n");
    PQclear(res);
    return 0;
}


