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
    
    vstr_t *strd = vstr_dup("aaaaaaa");
    vstr_assign(strd, "12345");
    vstr_print(strd, stdout);

    vstr_t* strc = vstr_concat(strd, str);
    vstr_print(strc, stdout);

    strc = vstr_append(strc, "-tuytutututuyt");
    vstr_print(strc, stdout);
    
    vstr_free(strc);
    vstr_free(strd);
    vstr_free(str);
    return 0;
} 