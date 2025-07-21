#ifndef _PD_DML_H_
#define _PD_DML_H_

#include <sqlite3.h>

typedef struct pd_dml_t pd_dml_t;

pd_dml_t* pd_dml_new();
void pd_dml_ctor(pd_dml_t* pd_dml,  sqlite3* db);
void pd_dml_dtor(pd_dml_t* pd_dml);
void pd_dml_free(pd_dml_t* pd_dml);


#endif