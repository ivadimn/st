#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_info.h"
#include "vstr.h"
#include "utils.h"

const char *line = "80.82.70.140 - - [19/Jul/2020:07:31:03 +0000]  \"GET /%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B HTTP/1.1\" 503 206  \"http://77.244.214.49:80/left.html\" "\
"\"Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:77.0) Gecko/20100101 Firefox/77.0\" \"-\"";
const char *line2 = "Pete Ivanov;250000;начальник Управления";
const char *url = "%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B";
const char *buf = "ИВАНОВЁ IVANOV";

int main(int argc, char** argv)
{
    /*vstr_array_t* lines = get_strings_from_file("data.csv");
    vstr_array_print(lines, stdout);

    long len = vstr_array_length(lines);
    for (long i = 0; i < len; i++)
    {
        vstr_t *s = vstr_array_get(lines, i);
        vstr_replace(s, " ;", 0);
    }
    
    
    vstr_array_print(lines, stdout);
    vstr_array_free(lines); */

    size_t len = strlen(buf);
    printf("%ld\n", len);

    for (size_t i = 0; i < len; i++)
    {
        printf("%2x ", buf[i]);
    }
    printf("\n");

    uint16_t *ibuf = (uint16_t*) buf;
    for (size_t i = 0; i < len / 2; i++)
    {
        printf("%x ", ibuf[i]);
    }
    printf("\n");

    
    vstr_t* str = vstr_dup(buf);
    vstr_print_data(str, stdout);
    vstr_tolower(str);
    vstr_print(str, stdout);
    vstr_print_data(str, stdout);
    vstr_free(str);
    return 0;
} 