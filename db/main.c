#include <stdio.h>
#include <sqlite3.h>

#include "db.h"
#include "pd.h"
#include "entity.h"
#include "vstrex.h"
#include "array.h"


int main(int argc, char** argv)
{
   
    array_t* arr = NULL;
    pd_t* pd = NULL;
    size_t count = 0;
    conn_t* conn = create_conn("/home/vadim/st/db/data.db");
    open_db(conn);
    
    pd_count(conn, &count);    
    printf("count: %ld\n", count);

    arr = new_array(A_TYPE_POINTER, count, sizeof(pd_t*));
    pd_select(conn, arr, NULL);

    for (size_t i = 0; i < count; i++)
    {
        get(arr, i, &pd);
        printf("id: %ld ", pd->id);
        vstr_print(pd->name, stdout);
    }
    
    
    close_db(conn);
    free_conn(conn);
  

    del_array(arr); 

    /* sqlite3 *db;    // указатель на базу данных
    sqlite3_stmt *res;  // указатель на скомпилированное выражение
 
    int rc  = sqlite3_open("data.db", &db);
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return 1;
    } 
    int age = 30;
    rc = sqlite3_prepare_v2(db, "Select id, name FROM pd;", -1, &res, 0);
     
    if (rc == SQLITE_OK) 
    {
        // привязываем параметры
        sqlite3_bind_int(res, 1, age);
        // перебираем все строки из результата
        while (sqlite3_step(res) == SQLITE_ROW) 
        {
            printf("Id: %lld\t", sqlite3_column_int64(res, 0));
            printf("Name: %s\t", sqlite3_column_text(res, 1));
            //printf("Age: %d\n", sqlite3_column_int(res, 2));
        } 
    }
    // удаляем скомпилированное выражение
    sqlite3_finalize(res);
    sqlite3_close(db); */


    
    return 0;
}