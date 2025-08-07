#ifndef _COMMON_H_
#define _COMMON_H_

#include <stddef.h>

#define DBOBJECT_NAME_LEN 64

typedef unsigned char bool_t;

typedef enum  type_t
{
    TYPE_NULL,
    TYPE_INT,
    TYPE_REAL,
    TYPE_TEXT,
    TYPE_BLOB
} type_t;

typedef struct base_t
{
    type_t type;
} base_t;

typedef struct null_t
{
    type_t type;
    void* value;
} null_t;

typedef struct int_t
{
    type_t type;
    long value;
} int_t;

typedef struct real_t
{
    type_t type;
    double value;
} real_t;

typedef struct text_t
{
    type_t type;
    char* value;
} text_t;

typedef struct blob_t
{
    type_t type;
    void* value;
} blon_t;

typedef union object_t
{
    base_t base;
    null_t null_val;
    int_t  int_val;
    real_t real_val;
    text_t text_val;
    blob_t blob_val;   
} object_t;


typedef struct sarray_t
{
    char** arr;
    size_t size;
    size_t length;

} sarray_t;

#endif