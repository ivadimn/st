#include <stdio.h>
#include "db.h"
#include "pd.h"
#include "entity.h"
#include "vstrex.h"


char *err_msg = NULL;

typedef int (*result_handel)(void *data, int argc, char **argv, char **col_name);

static int callback(void *data, int argc, char **argv, char **col_name){
    int i;
    vstr_array_t* d = NULL;
    if (data == NULL)
        return -1;
    d = (vstr_array_t*) data;

    //for(i=0; i<argc; i++){
    //  printf("%s = %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
    //}
    vstr_array_adds(d, argv[1]);
    
    return 0;
}


static int get_pd(sqlite3* db)
{
    int result;
    sqlite3_stmt* stmt; 

    if(sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Ошибка подготовки SQL-запроса: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    while((result = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        printf("id: %lld\n", sqlite3_column_int64(stmt, 0));
        printf("name: %s\n", sqlite3_column_text(stmt, 1));
        printf("----------------------------------------\n");
    }
    
    if(result != SQLITE_DONE) {
        printf("Ошибка выполнения SQL-запроса: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    return 0;
}

int main(int argc, char** argv)
{
    int result;
    conn_t* conn = create_conn("/home/vadim/st/db/data.db");
    open_db(conn);
    printf("Database was opened!!\n");

    vstr_array_t* data = vstr_array_create(10); 


    //get_pd(get_db(conn));
    result = sqlite3_exec(get_db(conn), sql, callback, (void*) data, &err_msg);
    if (result != SQLITE_OK)
    {
        printf("Error: %s\n", err_msg);
    }
    vstr_array_print(data, stdout);
    

    close_db(conn);
    free_conn(conn);

    /*pd_t* pd = pd_new();

    pd_ctor(pd, 100,  "Name 11");
    printf("id = %ld\n", entity_get_id((entity_t*)pd));
    vstr_t*  name = entity_get_name((entity_t*)pd);
    vstr_print(name, stdout);
    
    pd_dtor(pd);
    pdfree(pd);*/
    
    return 0;
}