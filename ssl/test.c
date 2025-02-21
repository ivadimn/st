#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_info.h"
#include "vstr.h"

const char *line = "80.82.70.140 - - [19/Jul/2020:07:31:03 +0000]  \"GET /%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B HTTP/1.1\" 503 206  \"http://77.244.214.49:80/left.html\" "\
"\"Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:77.0) Gecko/20100101 Firefox/77.0\" \"-\"";
const char *line2 = "Pete Ivanov;250000;начальник Управления";
const char *url = "%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B";

int main(int argc, char** argv)
{
    //handle_file("access.log");
    vstr_t* str = vstr_plus(4, "1111", "2222", "3333", "4444");
    vstr_print(str, stdout);
    
    vstr_t* go = vstr_dup("\"[");
    vstr_t* gc = vstr_dup("\"]");
    vstr_t* l = vstr_dup(line2);
    vstr_print(l, stdout);
    vstr_array_t* arr = vstr_array_create(10);
    //vstr_split1(arr, l, " ", go, gc);
    vstr_split(arr, l, ";", NULL, NULL);
    //printf("сделано\n");
    vstr_array_print(arr, stdout);

    vstr_assign(l, url);
    vstr_urldecode(l);
    vstr_print(l, stdout);

    vstr_free(l);
    vstr_free(go);
    vstr_free(gc);
    vstr_array_free(arr);
    vstr_free(str);
    return 0;
} 