#ifndef _PD_H_
#define _PD_H_

#include <stddef.h>
#include "db.h"
#include "param.h"
#include "vstrex.h"

typedef struct pd_t
{
    size_t id;
    vstr_t* name;
} pd_t;

// выделить память 
pd_t* pd_new();

int pd_select(conn_t* conn, void* data, param_list_t* params);
int pd_count(conn_t* conn, size_t* count);

// конструктор
void pd_ctor(pd_t* pd, size_t id, char* name);

void pd_dtor(pd_t* pd);

void pd_free(pd_t* pd);


#endif