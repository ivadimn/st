#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <stddef.h>

typedef struct entity_t entity_t;

entity_t* entity_new();
void entity_ctor(entity_t *e, size_t id);
void entity_dtor(entity_t *e);

size_t entity_get_id(entity_t* e);

#endif