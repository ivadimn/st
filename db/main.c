#include <stdio.h>
#include "db.h"


int main(int argc, char** argv)
{
    conn_t* conn = create_conn("data.db");
    open_db(conn);
    printf("Database was opened!!\n");
    close_db(conn);
    free_conn(conn);
    
    return 0;
}