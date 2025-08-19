#include <stdlib.h>
#include <string.h>
#include "common.h"

void __resize(varray_t* arr)
{
    object_t* new_items = (object_t*) malloc(sizeof(object_t) * (arr->size * 2));
    memcpy(new_items, arr->items, sizeof(object_t) * arr->size);
    arr->size *= 2;
    free(arr->items);
    arr->items = new_items;
}


void print_object(object_t obj, FILE* f)
{
    char buffer[256];
    switch (obj.base.type)
    {
    case TYPE_BLOB:
        snprintf(buffer, 255, "%p", obj.blob_val.value);
        break;
    case TYPE_INT:
        snprintf(buffer, 255, "%ld", obj.int_val.value);
        break;
    case TYPE_NULL:
        snprintf(buffer, 255, "%s", "NULL");
        break;    
    case TYPE_REAL:
        snprintf(buffer, 255, "%f", obj.real_val.value);
        break;    
    case TYPE_TEXT:
        snprintf(buffer, 255, "%s", obj.text_val.value);
        break;    
    default:
        break;
    }
    fwrite(buffer, sizeof(char), strlen((const char*) buffer), f);
    fwrite("\n", 1, 1, f);
    fflush(f);
}

varray_t* new_varray(size_t size)
{
    varray_t *arr = NULL;
    arr = (varray_t*) malloc(sizeof(varray_t));
    if (arr == NULL)
        return NULL;
    arr->items = (object_t*) malloc(sizeof(object_t) * size);
    if (arr->items == NULL)
        return NULL;

    arr->length = 0;
    arr->size = size;    
    return arr;    
}

void free_varray(varray_t *arr)
{
    if (arr->items)
        free(arr->items);
    free(arr);    
}

void varray_add_item(varray_t *arr, object_t item)
{
    if (arr->length == arr->size)
        __resize(arr);

    memcpy(&(arr->items[arr->length]), &item, sizeof(object_t));
    arr->length++;        
}

int varray_get_item(varray_t *arr, size_t index, object_t *item)
{
    if (index >= arr->length)
        return 1;
    memcpy(item, &(arr->items[index]), sizeof(object_t));    
    return 0;
}