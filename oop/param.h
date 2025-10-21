#ifndef _PARAM_H_
#define _PARAM_H_

#include <stddef.h>
#include <stdint.h>
#include "const.h"

typedef enum {SERIAL, INT, LONG, FLOAT, DOUBLE, CHAR, TEXT, BLOB} type_t;

typedef union value_t
{
    size_t pkey_value;
    int int_value;
    long long_value;
    float float_value;
    double double_value;
    char char_value;
    char *text_value;
    uint8_t* blob;
} value_t;

typedef struct param_t
{
    type_t type;
    value_t value;
} param_t;

typedef struct param_list_t
{
    param_t params[MAX_PARAMS];
    size_t size;
} param_list_t;


int param_list_add(param_list_t* listp, type_t type, value_t value);

#endif