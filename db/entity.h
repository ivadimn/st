#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <stddef.h>
#include "vstrex.h"

typedef struct entity_t entity_t;

entity_t* entity_new();
void entity_ctor(entity_t *e, size_t id, char* name);
void entity_dtor(entity_t *e);

size_t entity_get_id(entity_t* e);
vstr_t* entity_get_name(entity_t* e);

void entity_free(entity_t* e);


#endif