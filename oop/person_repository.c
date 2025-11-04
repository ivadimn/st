#include <stdlib.h>
#include "person_repository.h"
#include "person.h"
#include "person_p.h"
#include "postgres.h"
#include "row.h"
#include "../lib/src/log.h"
#include "../lib/src/utils.h"
#include "../lib/src/vstrex.h"

static char* SELECT_ALL = "SELECT id, first_name, second_name, surname, birthday FROM person ;";
static char* SELECT_PARAM = "SELECT id, first_name, second_name, surname, birthday FROM person ";
static char* INSERT_SQL = "INSERT INTO person(first_name, second_name, surname, birthday)\
                       VALUES($1, $2, $3, $4);";

static person_repository_t pr;

static array_t* __init_persons(size_t count)
{
    array_t * items = new_array(A_TYPE_VALUE, count, sizeof(person_t));
    return items;
}

static size_t __load_persons(param_list_t* params)
{
    size_t result = 0;
    PGresult* res;

    if (pr.items)
        free_person_repository();
    

    if (params != NULL)
        res = do_select(pr.conn, SELECT_PARAM, params, params->size);    
    else       
        res = do_select(pr.conn, SELECT_ALL, NULL, 0);
        
    if (res == NULL)
        return 0;

    result = PQntuples(res);
    pr.items = __init_persons(result + 10);
    pr.count = result;
    person_t p;
    for(size_t i = 0; i < result; i++) {
        p.entity.state = OLD;
        p.entity.id =  atoi(PQgetvalue(res, i, 0));
        set_first_name(&p, PQgetvalue(res, i, 1));
        set_second_name(&p,PQgetvalue(res, i, 2));
        set_surname(&p, PQgetvalue(res, i, 3));
        set_birthday_raw(&p, PQgetvalue(res, i, 4));
        put(pr.items, i, &p);
    }
    PQclear(res);
    return result;
}

static int __save()
{
    vstr_array_t *current, **list;
    array_t *ains, *aupd,  *adel,  *arr;

    size_t idx_ins = 0, idx_del = 0, idx_upd = 0;
    size_t *idx, pointer_index = 0;
    person_t psn;
    int is_handling = 0;
    size_t fcount = 4;

    //printf("%ld\n", sizeof(row_t));
    if (pr.change_counters.inserted > 0) {
        ains = new_array(A_TYPE_VALUE, pr.change_counters.inserted, sizeof(vstr_array_t*));
        is_handling = 1;
    }

    if (pr.change_counters.updated > 0) {
        aupd = new_array(A_TYPE_VALUE, pr.change_counters.updated, sizeof(vstr_array_t*));
        is_handling = 1;
    }

    if (pr.change_counters.deleted > 0) {
        adel = new_array(A_TYPE_VALUE, pr.change_counters.deleted, sizeof(vstr_array_t*));
        is_handling = 1;
    }
    if (!is_handling)
        return 0;
    
    list = (vstr_array_t**) alloc(sizeof(vstr_array_t*) *
         (pr.change_counters.inserted + pr.change_counters.updated + pr.change_counters.deleted));    
    for (size_t i = 0; i < pr.count; i++)
    {
        get(pr.items, i, &psn);
        switch (psn.entity.state)
        {
        case INSERTED:
            idx = &idx_ins;
            arr = ains;
            current = vstr_array_create(fcount);
            break;
        case DELETED:
            idx = &idx_del;
            arr =  adel;
            current = vstr_array_create(1);
            break;    
        case UPDATED:
            idx = &idx_upd;
            arr =  aupd;
            current = vstr_array_create(fcount + 1);
            break;    
        default:
            continue;
        }

        vstr_array_adds(current, psn.first_name);
        vstr_array_adds(current, psn.secong_name);
        vstr_array_adds(current, psn.surname);
        format_birthday(&psn);
        vstr_array_adds(current, psn.birthday.str);
        put(arr, *idx, &current);
        list[pointer_index++] = current;
        (*idx)++;
    }
    
    for (size_t i = 0; i < pr.change_counters.inserted; i++)
    {
        get(ains, i, &current);
        vstr_array_print(current, stdout);
        printf("\n--------------------------------\n");
    }
    

    if (pr.change_counters.inserted > 0) {
        do_insert(pr.conn, INSERT_SQL, ains, 4, pr.change_counters.inserted);
        del_array(ains);
    }

    if (pr.change_counters.updated > 0)
        free(aupd);  

    if (pr.change_counters.deleted > 0)
        free(adel);

    return 0;
} 

static int __insert_persons(entity_t* item, size_t count)
{
    person_t *person = (person_t*) item;
    person->entity.id = 0;
    person->entity.state = INSERTED;
    put(pr.items, pr.count, person);
    pr.count++;
    pr.change_counters.inserted++;
    return 0;
}

void init_person_repository(conn_t* conn)
{
    pr.conn = conn;
    pr.count = 0;
    pr.items = NULL;
    pr.rep.select = __load_persons;
    pr.rep.insert = __insert_persons; 
    pr.rep.save = __save;
    pr.change_counters.inserted = 0;
    pr.change_counters.deleted = 0;
    pr.change_counters.updated = 0;
}

void free_person_repository()
{
    if(pr.items) {
        del_array(pr.items);
        pr.count = 0;
    }
}

person_repository_t* get_person_repository()
{
    return &pr;
}

void print_persons()
{
    person_t p;
    for (size_t i = 0; i < pr.count; i++)
    {
        get(pr.items, i, &p);
        print_person(&p);
    }
    
}