#include <stdlib.h>
#include "dmlp.h"

dml_t* dml_new()
{
    return (dml_t*)malloc(sizeof(dml_t));
}
void dml_ctor(dml_t* dml, sqlite3* db)
{
    dml->db = db;
    dml->result_list = NULL;
}
void dml_dtor(dml_t* dml)
{

}
void dml_free(dml_t* dml)
{
    free(dml);
}
