#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

/* for ntohl/htonl */
#include <netinet/in.h>
#include <arpa/inet.h>

#include "postgres.h"

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
                b_fnum;

    /* Возвращает номер столбца, соответствующий данному имени столбца. */
    /* Используйте PQfnumber, чтобы избежать предположений о порядке полей в результате. */
    i_fnum = PQfnumber(res, "i");
    t_fnum = PQfnumber(res, "t");
    b_fnum = PQfnumber(res, "b");

    for (i = 0; i < PQntuples(res); i++)
    {
        char       *iptr;
        char       *tptr;
        char       *bptr;
        int         blen;
        int         ival;

        /* Получить значения полей (мы игнорируем возможность того, что они равны NULL!) */
        iptr = PQgetvalue(res, i, i_fnum);
        tptr = PQgetvalue(res, i, t_fnum);
        bptr = PQgetvalue(res, i, b_fnum);

        /*
        * Двоичное представление INT4 имеет сетевой порядок байтов, который
        * лучше привести к локальному порядку байтов. */
        ival = ntohl(*((uint32_t *) iptr));

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
        printf("\n\n");
    }
}

