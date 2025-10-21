#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "param.h"


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
    case SERIAL:
        param->value.pkey_value = value.pkey_value;
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


int param_list_add(param_list_t* listp, type_t type, value_t value)
{
         
    if (listp->size == MAX_PARAMS)
        return -1;

    if (__set_value(&(listp->params[listp->size]), type, value))
        return -1;
    
    listp->size++;
    return 0;
}