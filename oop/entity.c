#include "entity_p.h"

size_t entity_get_id(entity_t* entity)
{
    return entity->id;
}

void entity_set_id(entity_t* entity, size_t id)
{
    entity->id = id;
}