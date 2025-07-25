#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "db.h"
#include "pd.h"
#include "entity.h"
#include "vstrex.h"
#include "array.h"


char *err_msg = NULL;

size_t ids[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
char* names[] = {"111", "222", "333", "444", "555", "666", "777", "888", "999", 
    "10 10 10", "11 11 11 ", "12 12 12"};


int main(int argc, char** argv)
{
   
    conn_t* conn = create_conn("/home/vadim/st/db/data.db");
    open_db(conn);
    printf("Database was opened!!\n");

    close_db(conn);
    free_conn(conn);


    array_t* arr = new_array(A_TYPE_POINTER, 6, sizeof(pd_t*));
    pd_t **pd = NULL;
    pd_t *pdf = NULL;
    pd = (pd_t**)malloc(sizeof(pd_t*) * 12);
    for (size_t i = 0; i < 12; i++)
    {
        pd[i] = pd_new();
        pd_ctor(pd[i], ids[i],  names[i]);
        put(arr, i, &(pd[i]));
    }
    for (size_t i = 0; i < 6; i++)
    {
        put(arr, i, &(pd[i]));
    }

    putm(arr, 6, &(pd[6]), 6);
    
    for (size_t i = 0; i < 12; i++)
    {
        get(arr, i, &pdf);
        printf("id = %ld\n", entity_get_id((entity_t*)pdf));
        vstr_t*  name = entity_get_name((entity_t*)pdf);
        vstr_print(name, stdout);
    }

    for (size_t i = 0; i < 6; i++)
    {
        pd_free(pd[i]);
    }
    free(pd);

    del_array(arr);


    
    return 0;
}