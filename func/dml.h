#ifndef _DML_H_
#define _DML_H_

#include "common.h"

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
    char link_field[DBOBJECT_NAME_LEN * 2 + 1];
} table_t;

table_t* new_table(char* name, char *link_f, size_t count_fields, ...);
void free_table(table_t *t);

void str_fields(table_t *t, char* buf);

void print_table_info(table_t *t);

void dml_select1(char* sql, varray_t* tables, field_t* fields, varray_t* params);


#endif