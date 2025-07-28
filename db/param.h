#ifndef _PARAM_H_
#define _PARAM_H_

#include <stddef.h>
#include <stdint.h>

typedef enum {INT, LONG, FLOAT, DOUBLE, CHAR, TEXT, BLOB} type_t;


typedef union value_t
{
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
    param_t* params;
    size_t length;
    size_t size;
} param_list_t;


param_list_t* param_list_new(size_t size);
void param_list_free(param_list_t* listp);

int param_list_add(param_list_t* listp, type_t type, value_t value);

#endif