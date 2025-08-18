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


    str_fields(t, buf);
    printf("SELECT %s\n", buf);
    free_table(t);

    link_fields_t lf1 = {.f1 = "field1", .f2 = "field2", .op = "<="};
    printf("lf1: %s,  %s, %s\n", lf1.f1, lf1.f2, lf1.op);
    link_fields_t lf2 = lf1;
    printf("lf2: %s,  %s, %s\n", lf2.f1, lf2.f2, lf2.op);
    strncpy(lf1.f1, "filed2", 32);

    printf("lf1: %s,  %s, %s\n", lf1.f1, lf1.f2, lf1.op);
    printf("lf2: %s,  %s, %s\n", lf2.f1, lf2.f2, lf2.op);

    /*field_t f = {.name = "filed1", .pk = 0, .type = TYPE_INT};
    printf("name: %s\n", f.name);
    printf("pk: %d\n", f.pk);
    printf("type: %d\n", f.type);*/


    return 0;
}