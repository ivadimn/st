#include <stdio.h>
#include "db.h"
#include "pd.h"
#include "entity.h"


int main(int argc, char** argv)
{
    /*conn_t* conn = create_conn("data.db");
    open_db(conn);
    printf("Database was opened!!\n");
    close_db(conn);
    free_conn(conn);*/

    char name[255];

    pd_t* pd = pd_new();

    pd_ctor(pd, 100,  "Name 11");
    printf("id = %ld\n", entity_get_id((entity_t*)pd));
    pd_get_name(pd, name);
    printf("name - %s\n", name);

    pd_free(pd);
    
    return 0;
}