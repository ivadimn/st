#include <stdlib.h>
#include <string.h>
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

static int __set_value(param_t* param, type_t type, value_t value)
{
    switch (type)
    {
    case TEXT:
        param->value.text_value = (char*)malloc(sizeof(char) * strlen(value.text_value) + 1);
        if (param->value.text_value == NULL)
            return -1;        
        strncpy(param->value.text_value, value.text_value, strlen(value.text_value));
        break;
    case BLOB:
        param->value.blob = (uint8_t*)malloc(sizeof(uint8_t) * sizeof(value.blob));
        if (param->value.blob == NULL)
            return -1;
        memcpy(param->value.blob, value.blob, sizeof(value.blob)); 
        break;
    case INT:
        param->value.int_value = value.int_value;
        break;
    case LONG:
        param->value.long_value = value.long_value;
        break;
    case FLOAT:
        param->value.float_value = value.float_value;
        break;
    case DOUBLE:
        param->value.double_value = value.double_value;
        break;  
    case CHAR:
        param->value.char_value = value.char_value;
        break;                  
    default:
        return -1;
    }
    return 0;
}

param_list_t* param_list_new(size_t size)
{
    param_list_t *listp = (param_list_t*)malloc(sizeof(param_list_t));
    if (listp == NULL)
        return NULL;
    
    listp->params = (param_t*)malloc(sizeof(param_t) * size);
    if (listp->params == NULL)
        return NULL;
    listp->length = 0;
    listp->size = size;
}

void param_list_free(param_list_t* listp)
{
    free(listp->params);
    free(listp);    
}


int param_list_add(param_list_t* listp, type_t type, value_t value)
{
         
    if (listp->length = listp->size)
        return -1;

    if (__set_value(&(listp->params[listp->length]), type, value))
        return -1;
    
    listp->length++;
    return 0;
}