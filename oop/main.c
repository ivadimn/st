#include <stdio.h>
#include <stdint.h>

/* for ntohl/htonl */
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../lib/src/log.h"
#include "connection.h"
#include "postgres.h"
#include "person_repository.h"
#include "person.h"
#include "person_p.h"


void load_all_persons(conn_t *conn)
{
    PGresult* res = PQexec(conn->db, "SELECT * FROM person;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
        err("Ошибка выполнения запроса: %s", PQerrorMessage(conn->db));
        
    int ncols = PQnfields(res);
    for(int i = 0; i < ncols; i++) 
    {
        char *name = PQfname(res, i);
        printf(" %s", name); 
    }
    printf("\n");
    int nrows = PQntuples(res);
    for(int i = 0; i < nrows; i++) {
        char* id = PQgetvalue(res, i, 0);
        char* first_name = PQgetvalue(res, i, 1);
        char* second_name = PQgetvalue(res, i, 2);
        char* surname = PQgetvalue(res, i, 3);
        printf("%s %s %s %s \n", id, first_name, second_name, surname); 
    }
    printf("Total %d rows\n", nrows);
    PQclear(res);

}

void query_w_params(PGconn *conn, size_t len)
{
    PGresult   *res;
    const char *paramValues[len];
    int         paramLengths[len];
    int         paramFormats[len];
    uint32_t    binaryIntVal;

    /*
    * Цель этой программы — проиллюстрировать использование функции PQexecParams() с
    * внешними параметрами, а также двоичной передачей данных.
    *
    * В этом первом примере параметры передаются как текст, но
    * результаты принимаются в двоичном формате. Используя внешние параметры, мы можем избежать
    * утомительной возни с кавычками и экранированием, даже если
    * данные — текстовые. Обратите внимание, что нам не нужно ничего делать с
    * кавычками в значении параметра.
    */

   /* Вот наше нестандартное значение параметра */
    paramValues[0] = "русский язык";

    res = PQexecParams(conn,
                       "SELECT * FROM test1 WHERE t = $1",
                       1,       /* один параметр */
                       NULL,    /* пусть бэкэнд выведет тип параметра */
                       paramValues,
                       NULL,    /* не нужны длины параметров, так как текст */
                       NULL,    /* по умолчанию для всех текстовых параметров */
                       1);      /* запросить бинарные результаты */

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    show_binary_results(res);

    PQclear(res);

    /*
    * Во втором примере мы передаем целочисленный параметр в двоичной форме,
    * и снова получаем результаты в двоичной форме.
    *
    * Хотя мы сообщаем PQexecParams, что позволяем бэкенду определить
    * тип параметра, мы фактически форсируем решение, приводя символ параметра
    * в тексте запроса. Это хорошая мера безопасности при отправке
    * двоичных параметров.
    */



    /* Преобразовать целое число «2» в сетевой порядок байтов */
    binaryIntVal = htonl((uint32_t) 3);

    /* Set up parameter arrays for PQexecParams */
    paramValues[0] = (char *) &binaryIntVal;
    paramLengths[0] = sizeof(binaryIntVal);
    paramFormats[0] = 1;        /* binary */

    res = PQexecParams(conn,
                       "SELECT * FROM test1 WHERE i = $1::int4",
                       1,       /* one param */
                       NULL,    /* let the backend deduce param type */
                       paramValues,
                       paramLengths,
                       paramFormats,
                       1);      /* ask for binary results */

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    show_binary_results(res);

    PQclear(res);
}


int main(int argc, char** argv)
{
    conn_param_t* cp = init_conn_param("192.168.0.141", "5432", "dev", "7922448", "gaz");
    conn_t* conn = new_connection(cp);
     connect1(conn);

    // query_w_params(conn->db, 1);
    init_person_repository(conn);
    param_list_t params;
    params.size = 0;
    param_t param;
    value_t value;
    value.int_value = 7;
    init_param(&param, "id", ">=", INT, value);
    param_list_add(&params, &param);  
    value.int_value = 15;
    init_param(&param, "id", "<=", INT, value);
    param_list_add(&params, &param);  

    param_list_print(&params);
    LOAD_PERSONS(&params);
    print_persons();
        
    person_t* person = new_person();
    init_person(person, "Самойлова", "Дарья", "Сергеевна", "1982-09-02");
    INSERT_PERSONS(person, 1)
    
    init_person(person, "Цветкова", "Елена", "Васильевна", "1982-07-11");
    INSERT_PERSONS(person, 1)

    init_person(person, "Новицкий", "Илья", "Сергеевич", "1982-09-02");
    INSERT_PERSONS(person, 1)

    SAVE_PERSONS()

    disconnect(conn);
    del_connection(conn);
    release_conn_param(cp);
    
    return 0;
}