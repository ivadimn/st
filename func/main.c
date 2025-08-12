#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "dml.h"

int main(int argc, char** argv)
{
    object_t obj;
    varray_t *arr;
    size_t index = 0;

    table_t *t = new_table("Table", "id", 3, "id", "name", "comment");
    print_table_info(t);
    free_table(t);

    /*field_t f = {.name = "filed1", .pk = 0, .type = TYPE_INT};
    printf("name: %s\n", f.name);
    printf("pk: %d\n", f.pk);
    printf("type: %d\n", f.type);*/


    return 0;
}