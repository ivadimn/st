#ifndef _PERSON_P_H_
#define _PERSON_P_H_

#include "db_type.h"
#include "entity_p.h"
#include "const.h"


typedef struct person_t
{
    entity_t entity;
    char first_name[NAME_LEN];
    char secong_name[NAME_LEN];
    char surname[NAME_LEN];
    birthday_t birthday;

} person_t;

#endif