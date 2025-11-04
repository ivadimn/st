#ifndef _ENTITY_P_H_
#define _ENTITY_P_H_

#include <stddef.h>

typedef enum {OLD, INSERTED, UPDATED, DELETED} entity_state_t;

typedef struct entity_t
{
    size_t id;
    entity_state_t state;
} entity_t;



#endif