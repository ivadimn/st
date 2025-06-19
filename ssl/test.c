#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_info.h"
#include "vstrex.h"
#include "utils.h"


const char *line = "80.82.70.140 - - [19/Jul/2020:07:31:03 +0000]  \"GET /%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B HTTP/1.1\" 503 206  \"http://77.244.214.49:80/left.html\" "\
"\"Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:77.0) Gecko/20100101 Firefox/77.0\" \"-\"";
const char *line2 = "Pete Ivanov;250000;начальник Управления";
const char *url = "%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B";
const char *buf = "ивановё ivanov";
const char *buf2 = "abcрсту";

int main(int argc, char** argv)
{
    vstr_t* str = vstr_create(32);
    vstr_assign(str, buf2);
    vstr_print(str, stdout);
    vstr_print_param(str);
    printf("\n");

    vstr_t* strd = vstr_dup(line2);
    vstr_print(strd, stdout);
    vstr_print_param(strd);
    printf("\n");

    vstr_t* strp = vstr_plus(3, line2, buf, buf2);
    vstr_print(strp, stdout);

    vstr_t* strc = vstr_concat(strd, str);
    vstr_print(strc, stdout);
    printf("\n");
    str = vstr_append(str, "добавили слова");
    vstr_print(str, stdout);
    long index = vstr_instr(str, "доб");
    printf("index = %ld\n", index);

    vstr_t *substr = vstr_substr(str, 3, 9);
    vstr_print(substr, stdout);
    vstr_print_param(substr);

    vstr_t* l = vstr_dup(line2);
    vstr_split(l, ";", NULL, NULL);

    return 0;
} 