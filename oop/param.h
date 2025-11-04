#ifndef _PARAM_H_
#define _PARAM_H_

#include <stddef.h>
#include <stdint.h>
#include "const.h"

typedef enum {INT, LONG, FLOAT, DOUBLE, TEXT, BLOB} type_t;

typedef union value_t
{
    int int_value;
    long long_value;
    float float_value;
    double double_value;
    char *text_value;
    uint8_t* blob;
} value_t;

typedef struct param_t
{
    char name[PARAM_NAME_LEN];
    char op[OP_LEN];
    type_t type;
    value_t value;
    char text_value[TEXT_VALUE_LEN];
} param_t;

typedef struct param_list_t
{
    param_t params[MAX_PARAMS];
    size_t size;
} param_list_t;

param_list_t* new_param_lists(size_t count);
void del_param_list(param_list_t* pl);

void init_param(param_t *p, char* name, char* op, type_t type, value_t value);
int param_list_add(param_list_t* listp, param_t *p);
void print_param(param_t* p);
void param_list_print(param_list_t* listp);

#endif