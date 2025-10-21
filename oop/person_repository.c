#include <stdlib.h>
#include "person_repository.h"
#include "person.h"
#include "person_p.h"
#include "../lib/src/log.h"

static char* SELECT_ALL = "SELECT id, first_name, second_name, surname, birthday FROM person;";


static person_repository_t pr;

static person_t* __init_persons(size_t count)
{
    person_t * items = (person_t*) malloc(sizeof(person_t) * count);
    if (items == NULL)
        crit("Ошибка распределения памяти для структуры Person");
    
    return items;
}

static size_t __load_persons(param_list_t* params)
{
    size_t result = 0;

    if (pr.items)
        free_person_repository();
    

    PGresult* res = PQexec(pr.conn->db, SELECT_ALL);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        err("Ошибка загрузки : %s", PQerrorMessage(pr.conn->db));
        return 0;
    }
        
    /*
    * обработку результата выделить в отдельную функцию
    */
    result = PQntuples(res);
    pr.items = __init_persons(result);
    pr.count = result;
    for(size_t i = 0; i < result; i++) {
        pr.items[i].entity.id =  atoi(PQgetvalue(res, i, 0));
        set_first_name(&pr.items[i], PQgetvalue(res, i, 1));
        set_second_name(&pr.items[i],PQgetvalue(res, i, 2));
        set_surname(&pr.items[i], PQgetvalue(res, i, 3));
        set_birthday_raw(&pr.items[i], PQgetvalue(res, i, 4));
    }
    PQclear(res);
    return result;
}


void init_person_repository(conn_t* conn)
{
    pr.conn = conn;
    pr.count = 0;
    pr.items = NULL;
    pr.rep.select = __load_persons;
}

void free_person_repository()
{
    if(pr.items) {
        free(pr.items);
        pr.count = 0;
    }
}

person_repository_t* get_person_repository()
{
    return &pr;
}

void print_persons()
{
    for (size_t i = 0; i < pr.count; i++)
    {
        print_person(&pr.items[i]);
    }
    
}