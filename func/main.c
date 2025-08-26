#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <libpq-fe.h>

#include "dml.h"
#include "connection.h"

char buf[512];
char sql[SQL_QUERY_LEN];

int main(int argc, char** argv)
{
    /*object_t obj;
    varray_t *arr;
    size_t index = 0;

    table_t *t = new_table("Table", 3, "id", "name", "comment");
    
    join_t *root = create_join(NULL, t, 0);

    table_t *t1 = new_table("Table_1", 3, "id1", "name1", "comment1");

    link_fields_t lf1 = {.f1 = "field1", .f2 = "field2", .op = "<="};
    link_fields_t lf2 = {.f1 = "field3", .f2 = "field4", .op = "="};

    join_t *j1 = create_join(root, t1, 2,  &lf1, &lf2);
    printf("Table name: %s\n", j1->table.name);
    
    print_join(root, 1);

    printf("--------------------------------------------------------\n");
    dml_select1(sql, root, NULL);
    printf("SQL: %s\n", sql);

    
    free_join(j1);
    free_join(root);
    free_table(t); */

    
    conn_param_t* cp = init_conn_param("10.0.0.101", "5432", "dev", "7922448", "gaz");
    conn_t* conn = new_connection(cp);
    connect1(conn);
    disconnect(conn);
    del_connection(conn);
    release_conn_param(cp);
    
    return 0;
}