#ifndef _PERSON_REPOSITORY_H_
#define _PERSON_REPOSITORY_H_

#include "connection.h"
#include "repository.h"
#include "person.h"
#include "param.h"

typedef struct person_repository_t
{
    repository_t rep;
    conn_t *conn;
    person_t* items;
    size_t count;
} person_repository_t;


#define LOAD_PERSONS(params)                            \
do                                                      \
{                                                       \
    person_repository_t* r = get_person_repository();   \
    r->count = r->rep.select(params);                   \
} while (0);                                            \


void init_person_repository(conn_t* conn);
void free_person_repository();
person_repository_t* get_person_repository();
void print_persons();


#endif