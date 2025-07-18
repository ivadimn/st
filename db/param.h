#ifndef _PARAM_H_
#define _PARMA_H_

#include <stddef.h>

typedef enum type_t type_t;
typedef union value_t value_t;

typedef struct param_t param_t;
typedef struct param_list_t param_list_t;

param_list_t* param_list_new(size_t size);
void param_list_free(param_list_t* listp);

int param_list_add(param_list_t* listp, type_t type, value_t value);

#endif