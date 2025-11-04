#ifndef _REPOSITORY_H_
#define _REPOSITORY_H_

#include "param.h"
#include "entity.h"
#include "../lib/src/array.h"


typedef size_t (*dml_select)(param_list_t*);
typedef int (*dml_update)(entity_t* entity, size_t count);
typedef int (*dml_save)(void);

typedef struct repository_t
{
    dml_select select;
    dml_update insert;
    dml_update update;
    dml_update remove;
    dml_save   save;  
} repository_t;


#endif