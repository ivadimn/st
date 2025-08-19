#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "dml.h"

char buf[512];

int main(int argc, char** argv)
{
    object_t obj;
    varray_t *arr;
    size_t index = 0;

    table_t *t = new_table("Table", 3, "id", "name", "comment");
    print_table_info(t);

    table_t t2 = *t;
    
    printf("address t: %p\n", (void*)t);
    printf("address t->fields: %p\n", (void*)t->fields);
    printf("address t2: %p\n", (void*)&t2);
    printf("address t2->fields: %p\n", (void*)&(t2.fields));

    print_table_info(&t2);


    str_fields(t, buf);
    printf("SELECT %s\n", buf);

    link_fields_t lf1 = {.f1 = "field1", .f2 = "field2", .op = "<="};
    link_fields_t lf2 = {.f1 = "field3", .f2 = "field4", .op = "="};

    join_t *root = create_join(t, 2,  &lf1, &lf2);


    free_table(t);
   

    /*field_t f = {.name = "filed1", .pk = 0, .type = TYPE_INT};
    printf("name: %s\n", f.name);
    printf("pk: %d\n", f.pk);
    printf("type: %d\n", f.type);*/


    return 0;
}