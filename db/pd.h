#ifndef _PD_H_
#define _PD_H_

#include <stddef.h>

typedef struct pd_t pd_t;

// выделить память 
pd_t* pd_new();

// конструктор
void pd_ctor(pd_t* pd, size_t id, char* name);

void pd_dtor(pd_t* pd);

void pd_free(pd_t* pd);


#endif