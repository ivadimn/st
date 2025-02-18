#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_info.h"
#include "vstr.h"


int main(int argc, char** argv)
{
    //handle_file("access.log");
    vstr_t* str = vstr_plus(4, "1111", "2222", "3333", "4444");
    vstr_print(str, stdout);
    
    //vstr_t* sub = vstr_create(1);
    vstr_t* sub = vstr_substr(str, 15, 16);
    printf("сделано\n");
    //vstr_print(sub, stdout);

    vstr_free(sub);
    vstr_free(str);
    return 0;
} 