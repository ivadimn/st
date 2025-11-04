#ifndef _PERSON_REPOSITORY_H_
#define _PERSON_REPOSITORY_H_

#include "connection.h"
#include "repository.h"
#include "person.h"
#include "param.h"
#include "../lib/src/array.h"


typedef struct person_repository_t
{
    repository_t rep;
    conn_t *conn;
    array_t* items;
    size_t count;
    struct {
        size_t inserted;
        size_t updated;
        size_t deleted;
    } change_counters;
} person_repository_t;


#define LOAD_PERSONS(params)                            \
do                                                      \
{                                                       \
    person_repository_t* rs = get_person_repository();  \
    rs->rep.select((params));                           \
} while (0);                                            \

#define INSERT_PERSONS(person, count)                   \
do                                                      \
{                                                       \
    person_repository_t* ri = get_person_repository();  \
    entity_t* entity = (entity_t*)(person);             \
    ri->rep.insert(entity, (count));                    \
} while (0);                                            \

#define SAVE_PERSONS()                                  \
do                                                      \
{                                                       \
    person_repository_t* rs = get_person_repository();  \
    rs->rep.save();                                     \
} while (0);                                            \

void init_person_repository(conn_t* conn);
void free_person_repository();
person_repository_t* get_person_repository();
void print_persons();


#endif