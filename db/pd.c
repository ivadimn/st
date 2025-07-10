#include <string.h>
#include <stdlib.h>

#include "entityp.h"

#define NAME_LEN    256

typedef struct 
{
    entity_t entity;
    char name[NAME_LEN]; 

} pd_t;

pd_t* pd_new()
{

}
void pd_ctor(pd_t* pd, char* name);
void pd_dtor(pd_t* pd);

char * pd_get_name(pd_t* pd, char* name);