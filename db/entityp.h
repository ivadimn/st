#ifndef _ENTITYP_H_
#define _ENTITYP_H_

#include <stddef.h>
#include "vstrex.h"

typedef int (*result_list_t) (void *stmt, void* data);

typedef struct entity_t
{
     size_t id;
     vstr_t* name;
     result_list_t result_list;
} entity_t;



#endif