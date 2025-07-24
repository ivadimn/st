#include <string.h>
#include <stdlib.h>
#include "db.h"

#include "entityp.h"
#include "entity.h"
#include "log.h"

const char *sql = "Select id, name FROM pd;";

typedef struct 
{
    entity_t entity;
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
    entity_ctor((entity_t*)pd, id, name);
}

void pd_dtor(pd_t* pd)
{
    entity_dtor((entity_t*)pd);
}

void pd_free(pd_t* pd)
{
    free(pd);
}