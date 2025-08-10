#ifndef _DML_H_
#define _DML_H_

#include "common.h"

typedef struct field_t
{
    type_t type;
    char name[32];
    bool_t pk;

} field_t;

typedef struct table_t
{
    char name[32];
    field_t *fields;
    field_t link_field;
} table_t;


void dml_select1(char* sql, varray_t* tables, field_t* fields, varray_t* params);


#endif