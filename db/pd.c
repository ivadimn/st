#include <string.h>
#include <stdlib.h>

#include "entityp.h"
#include "entity.h"
#include "log.h"

#define NAME_LEN    255

typedef struct 
{
    entity_t entity;
    char name[NAME_LEN]; 

} pd_t;

pd_t* pd_new()
{
    pd_t* pd = (pd_t*) malloc(sizeof(pd_t));
    if (pd == NULL)
    {
        crit("Ошибка выделения памяти под объект <pd_t>\n");
    }
    return pd;
}
void pd_ctor(pd_t* pd, size_t id, char* name)
{
    entity_ctor((entity_t*)pd, id);
    strncpy(pd->name, name, NAME_LEN);
}
void pd_dtor(pd_t* pd)
{}

char * pd_get_name(pd_t* pd, char* name)
{
    size_t len = strlen(pd->name);
    strncpy(name, pd->name, len);
    return name;
}

void pd_free(pd_t* pd)
{
    free(pd);
}