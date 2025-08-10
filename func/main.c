#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

int main(int argc, char** argv)
{
    object_t obj;
    varray_t *arr;
    size_t index = 0;

    arr = new_array(10);
    obj.base.type = TYPE_INT;
    obj.int_val.value = 25;
    array_add_item(arr, obj);

    obj.base.type = TYPE_REAL;
    obj.real_val.value = 104.567;
    array_add_item(arr, obj);

    obj.base.type = TYPE_TEXT;
    obj.text_val.value = "Text value 1";
    array_add_item(arr, obj);

    obj.base.type = TYPE_TEXT;
    obj.text_val.value = "Text value 2";
    array_add_item(arr, obj);
   
    while (array_get_item(arr, index, &obj) == 0)
    {
        print_object(obj, stdout);
        index++;
    }
    
    return 0;
}