#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_info.h"
#include "vstrex.h"
#include "utils.h"


const char *line = "80.82.70.140 - - [19/Jul/2020:07:31:03 +0000]  \"GET /%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B HTTP/1.1\" 503 206  \"http://77.244.214.49:80/left.html\" "\
"\"Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:77.0) Gecko/20100101 Firefox/77.0\" \"-\"";
const char *line2 = "Pete Ivanov;250000;ЁНачальник Управления";
const char *url = "%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B";
const char *buf = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const char *buf2 = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

int main(int argc, char** argv)
{
    vstr_t* s1 = vstr_dup(buf);
    vstr_print(s1, stdout);
    vstr_t* s2 = vstr_dup(buf2);
    vstr_print(s2, stdout);
    //print_delta(s1, s2);

    vstr_tolower(s1);
    vstr_print(s1, stdout);

    vstr_toupper(s2);
    vstr_print(s2, stdout);

    vstr_t* s3 = vstr_dup(line2);

    vstr_array_t *arr = vstr_array_create(5);
    vstr_array_addv(arr, s1);
    vstr_array_addv(arr, s2);
    vstr_array_addv(arr, s3);

    vstr_array_print(arr, stdout);

    vstr_array_free(arr);
    //vstr_free(s1);
    //vstr_free(s2);
    return 0;
} 