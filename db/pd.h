#ifndef _PD_H_
#define _PD_H_



typedef struct pd_t pd_t;

pd_t* pd_new();
void pd_ctor(pd_t* pd, char* name);
void pd_dtor(pd_t* pd);

char * pd_get_name(pd_t* pd, char* name);


#endif