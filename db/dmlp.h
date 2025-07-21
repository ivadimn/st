#ifndef _DMLP_H_
#define _DMLP_H_

#include <sqlite3.h>

typedef int (*result_list_t) (void *stmt, void* data);

typedef struct dml_t
{
    sqlite3* db;
    result_list_t result_list;
} dml_t;



#endif`