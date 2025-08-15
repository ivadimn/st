#ifndef _DML_H_
#define _DML_H_

#include "common.h"

#define OP_LEN 3

typedef struct link_fields_t
{
    char f1[DBOBJECT_NAME_LEN * 2 + 1];
    char f2[DBOBJECT_NAME_LEN * 2 + 1];
    char op[OP_LEN];
} link_fields_t;


typedef struct link_tables_t
{
    
} link_tables_t;


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

table_t* new_table(char* name, size_t count_fields, ...);
void free_table(table_t *t);

void str_fields(table_t *t, char* buf);

void print_table_info(table_t *t);

void dml_select1(char* sql, varray_t* tables, field_t* fields, varray_t* params);


#endif