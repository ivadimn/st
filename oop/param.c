
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "param.h"
#include "../lib/src/utils.h"

param_list_t* new_param_lists(size_t count)
{
    param_list_t *pl = (param_list_t*) alloc(sizeof(param_list_t) * count);
    for (size_t i = 0; i < count; i++)
    {
        pl[i].size = 0;
    }
    return pl;
}

void del_param_list(param_list_t* pl)
{
    free(pl);
}

void print_param(param_t* p)
{
    printf("%s %s %s, тип: %d", p->name, p->op, p->text_value, p->type);
    if (p->type == TEXT)
        printf(", %s\n", p->value.text_value);
    else 
        printf("\n");    
}

void init_param(param_t *p, char* name, char* op, type_t type, value_t value)
{
    strncpy(p->name, name, NAME_LEN);
    strncpy(p->op, op, OP_LEN);
    p->value = value;
    p->type = type;
    switch (type)
    {
        case INT:
            snprintf(p->text_value, PARAM_LEN, "%d", p->value.int_value);
            break;
        case LONG:
            snprintf(p->text_value, PARAM_LEN, "%ld", p->value.long_value);
            break;
        case FLOAT:
            snprintf(p->text_value, PARAM_LEN, "%f", p->value.float_value);
            break;
        case DOUBLE:
            snprintf(p->text_value, PARAM_LEN, "%f", p->value.double_value);
            break; 
        case TEXT:
            snprintf(p->text_value, PARAM_LEN, "%s", "Pointer");
            break;     
    default:
        break;
    }
}


int param_list_add(param_list_t* listp, param_t* param)
{
         
    if (listp->size == MAX_PARAMS)
        return 1;

    memcpy(&(listp->params[listp->size]), param, sizeof(param_t));    
    listp->size++;

    return 0;
}

void param_list_print(param_list_t* listp)
{
    for (size_t i = 0; i < listp->size; i++)
    {
        print_param(&(listp->params[i]));
    }
    
}