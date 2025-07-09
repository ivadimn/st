#include <stdlib.h>
#include "log.h"
#include "entityp.h"


entity_t* entity_new()
{
    entity_t* e = (entity_t*) malloc(sizeof(entity_t));
    if (e == NULL)
    {
        crit("Ошибка выделения памяти под объетк <entity_t>\n");
    }
    return e;
    
}
void entity_ctor(entity_t *e, size_t id)
{
    e->id = id;
}
void entity_dtor(entity_t *e)
{

}

size_t entity_get_id(entity_t* e)
{
    return e->id;
}




