#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <stddef.h>

typedef struct entity_t entity_t;

size_t entity_get_id(entity_t* entity);
void entity_set_id(entity_t* entity, size_t id);

#endif