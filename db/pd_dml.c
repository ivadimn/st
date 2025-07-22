#include <stdlib.h>
#include <sqlite3.h>

#include "dml.h"
#include "dmlp.h"

const char *sql_select_all = "Select id, name FROM pd;";

typedef struct pd_dml_t
{
    dml_t dml;
} pd_dml_t;

static int __result_list(void *stmt, void* data)
{
        
}


pd_dml_t* pd_dml_new()
{
    return (pd_dml_t*) malloc(sizeof(pd_dml_t));
}

void pd_dml_ctor(pd_dml_t* pd_dml,  sqlite3* db)
{
    dml_t* dml = (dml_t*) pd_dml;
    dml_ctor(dml, db);
    pd_dml->dml.result_list = __result_list;

}

void pd_dml_dtor(pd_dml_t* pd_dml)
{

}
void pd_dml_free(pd_dml_t* pd_dml)
{
    free(pd_dml);
}
