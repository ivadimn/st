#ifndef _COMMON_H_
#define _COMMON_H_

#include <stddef.h>
#include <stdio.h>

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
} blob_t;

typedef union object_t
{
    base_t base;
    null_t null_val;
    int_t  int_val;
    real_t real_val;
    text_t text_val;
    blob_t blob_val;   
} object_t;


typedef struct varray_t
{
    object_t *items;
    size_t size;
    size_t length;

} varray_t;

//object functions

void print_object(object_t obj, FILE* f);

//array functions
varray_t* new_varray(size_t size);
void free_varray(varray_t *arr);

void varray_add_item(varray_t *arr, object_t item);
int varray_get_item(varray_t *arr, size_t index, object_t *item);

#endif