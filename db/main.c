#include <stdio.h>
#include "db.h"
#include "pd.h"
#include "entity.h"
#include "vstrex.h"
#include "array.h"


char *err_msg = NULL;

size_t ids[] = {1, 2, 3, 4, 5, 6};
char* names[] = {"111", "222", "333", "444", "555", "666"};


int main(int argc, char** argv)
{
   
    conn_t* conn = create_conn("/home/vadim/st/db/data.db");
    open_db(conn);
    printf("Database was opened!!\n");

    close_db(conn);
    free_conn(conn);


    array_t* arr = new_array(A_TYPE_POINTER, 6, sizeof(pd_t*));
    pd_t* pd = NULL;
    for (size_t i = 0; i < 6; i++)
    {
        pd = pd_new();
        pd_ctor(pd, ids[i],  names[i]);
        put(arr, i, &pd);
    }
    
    for (size_t i = 0; i < 6; i++)
    {
        get(arr, i, &pd);
        printf("id = %ld\n", entity_get_id((entity_t*)pd));
        vstr_t*  name = entity_get_name((entity_t*)pd);
        vstr_print(name, stdout);
        pd_dtor(pd);
        pd_free(pd);
    }
    del_array(arr);
    
    return 0;
}