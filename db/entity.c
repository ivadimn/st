#include <stdlib.h>
#include "log.h"
#include "entity.h"
#include "vstrex.h"


entity_t* entity_new()
{
    entity_t* e = (entity_t*) malloc(sizeof(entity_t));
    if (e == NULL)
    {
        crit("Ошибка выделения памяти под объект <entity_t>\n");
    }
    return e;
    
}
void entity_ctor(entity_t *e, size_t id, char *name)
{
    e->name = vstr_dup(name);
    e->id = id;
}

void entity_dtor(entity_t *e)
{
    vstr_free(e->name);
}

size_t entity_get_id(entity_t* e)
{
    return e->id;
}

vstr_t* entity_get_name(entity_t* e)
{
    return e->name;
}

void entity_set_id(entity_t* e, size_t id)
{
    e->id = id;
}
void entity_set_name(entity_t* e, vstr_t* str)
{
    vstr_copy(e->name, str, 0, vstr_len(str));    
}

void entity_free(entity_t* e)
{
    free(e);
}






