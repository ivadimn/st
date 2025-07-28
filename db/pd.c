#include <string.h>
#include <stdlib.h>
#include "db.h"

#include "pd.h"
#include "log.h"
#include "array.h"

const char *sql = "Select id, name FROM pd;";
const char *sql_count = "Select COUNT(*) FROM pd;";

static int _handle_select(sqlite3_stmt *stmt, void* data, param_list_t* params) 
{
    array_t* arr = (array_t*) data;
    pd_t* pd = NULL;
    int result;
    size_t index = 0;
    while ((result = sqlite3_step(stmt)) == SQLITE_ROW) 
    {
        pd = pd_new();
        pd_ctor(pd, sqlite3_column_int(stmt, 0), (char*)sqlite3_column_text(stmt, 1));
        put(arr, index, &pd);
        index++;
        //printf("Id: %d\t", sqlite3_column_int(stmt, 0));
        //printf("Name: %s\n", sqlite3_column_text(stmt, 1));
    } 
    return result;
}

int pd_select(conn_t* conn, void* data, param_list_t* params)
{
    return selectv(conn, sql, _handle_select, data, params);       
}

int pd_count(conn_t* conn, size_t* count)
{
    int result = countv(conn, sql_count, count);
    return result;
}

pd_t* pd_new()
{
    pd_t* pd = (pd_t*) malloc(sizeof(pd_t));
    if (pd == NULL)
    {
        crit("Ошибка выделения памяти под объект <pd_t>\n");
    }
    return pd;
}
void pd_ctor(pd_t* pd, size_t id, char* name)
{
    pd->id = id;
    pd->name = vstr_dup(name);
}

void pd_dtor(pd_t* pd)
{
    vstr_free(pd->name);
}

void pd_free(pd_t* pd)
{
    free(pd);
}