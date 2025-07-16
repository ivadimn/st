#ifndef _ENTITYP_H_
#define _ENTITYP_H_

#include <stddef.h>
#include "vstrex.h"

typedef struct entity_t
{
     size_t id;
     vstr_t* name;

} entity_t;



#endif