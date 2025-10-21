#ifndef _REPOSITORY_H_
#define _REPOSITORY_H_

#include "param.h"

typedef size_t (*dml_select)(param_list_t*);
typedef int (*dml_update)(param_list_t*);

typedef struct repository_t
{
    dml_select select;
    dml_update insert;
    dml_update update;
    dml_update remove;
} repository_t;


#endif