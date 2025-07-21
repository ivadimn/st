#ifndef _DML_H_
#define _DML_H_

#include <sqlite3.h>

typedef struct dml_t dml_t;

dml_t* dml_new();
void dml_ctor(dml_t* dml,  sqlite3* db);
void dml_dtor(dml_t* dml);
void dml_free(dml_t* dml);


#endif