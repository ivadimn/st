#include <stdio.h>
#include "db.h"
#include "pd.h"
#include "entity.h"
#include "vstrex.h"


char *err_msg = NULL;



int main(int argc, char** argv)
{
   
    conn_t* conn = create_conn("/home/vadim/st/db/data.db");
    open_db(conn);
    printf("Database was opened!!\n");

    close_db(conn);
    free_conn(conn);

    pd_t* pd = pd_new();

    pd_ctor(pd, 100,  "Name 11");
    printf("id = %ld\n", entity_get_id((entity_t*)pd));
    vstr_t*  name = entity_get_name((entity_t*)pd);
    vstr_print(name, stdout);
    
    pd_dtor(pd);
    pd_free(pd);
    
    return 0;
}