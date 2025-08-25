#ifndef _DML_H_
#define _DML_H_

#include "common.h"
#include "../lib/src/array.h"

#define OP_LEN 3
#define SEL_BUFF_LEN 1024
#define SQL_QUERY_LEN 2048

typedef struct join_t join_t;

typedef struct link_fields_t
{
    char f1[DBOBJECT_NAME_LEN * 2 + 1];
    char f2[DBOBJECT_NAME_LEN * 2 + 1];
    char op[OP_LEN];
} link_fields_t;

typedef struct field_t
{
    type_t type;
    char name[DBOBJECT_NAME_LEN + 1];
    bool_t pk;

} field_t;

typedef struct table_t
{
    char name[DBOBJECT_NAME_LEN + 1];
    size_t fcount;
    field_t *fields;
} table_t;


typedef struct join_t
{
    join_t* parent;
    table_t table;
    link_fields_t *lf;
    size_t count_lf;
    size_t count_joins;
    array_t* joins;
} join_t;


/*
* функции работы с таблицами
*/
table_t* new_table(char* name, size_t count_fields, ...);
void free_table(table_t *t);

void str_fields(table_t *t, char* buf);

void print_table_info(table_t *t);

/*
* функции join_t
*/
join_t * create_join(join_t* parent, table_t *table, size_t count_lf, ...);
void free_join(join_t* join);

void print_join(join_t *join, int level);



void dml_select1(char* sql, join_t* join, varray_t* params);


#endif