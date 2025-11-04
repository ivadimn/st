#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_info.h"
#include "utils.h"
#include "../lib/src/vstrex.h"
#include "../lib/src/array.h"


const char *line = "80.82.70.140 - - [19/Jul/2020:07:31:03 +0000]  \"GET /%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B HTTP/1.1\" 503 206  \"http://77.244.214.49:80/left.html\" "\
"\"Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:77.0) Gecko/20100101 Firefox/77.0\" \"-\"";
const char *line2 = "Pete Ivanov;250000;ЁНачальник Управления";
const char *url = "%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B";
const char *buf = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const char *buf2 = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";


uint16_t* svalue(uint8_t* s1) {

    size_t len = strlen((const char*)s1);
    uint16_t *data = (uint16_t*)malloc (sizeof(uint16_t) * len);
    size_t i = 0, index = 0;
    
    while(i < len)
    {
        if (s1[i] < 128)
        {
            data[index++] = s1[i] & 0x00ff; 
            i++;
        }
        else 
        {
            data[index] = s1[i];
            data[index] = (data[index] << 8) | s1[i+1];
            index++;
            i += 2;
        }
    }
    return data;
}


uint16_t* fvalue(uint16_t* s1) {

    size_t len = strlen((const char*)s1);
    uint16_t *data = (uint16_t*)malloc (sizeof(uint16_t) * len);
    size_t i = 0, index = 0;
    
    while(i < len)
    {
        if (s1[i] < 128)
        {
            data[index++] = s1[i] & 0x00ff; 
            i++;
        }
        else 
        {
            data[index] = s1[i];
            data[index] = (data[index] << 8) | s1[i+1];
            index++;
            i += 2;
        }
    }
    return data;
}

void reset() {
    size_t count = 4;
    uint16_t *ptr = (uint16_t*) malloc(count * sizeof(uint16_t));
    for (size_t i = 0; i < count; i++)
    {
        ptr[i] = i;
    }
    count = 8;
    ptr = (uint16_t*) realloc(ptr, count * sizeof(uint16_t));
    for (size_t i = 0; i < count; i++)
    {
        printf("%d\n", ptr[i]);
    }
}

int main(int argc, char** argv)
{
    // vstr_t* s0 = vstr_create(256);
    // vstr_assign(s0, " WHERE ");
    // vstr_plusv(s0, 4, "один;", "two;", "три;", "four;");
    // vstr_print(s0, stdout);
    // vstr_plusv(s0, 4, "пять;", "six;", "семь;", "eight;");
    // vstr_print(s0, stdout);

    // vstr_t* s2 = vstr_dup(buf);
    // vstr_tolower(s2);
    // vstr_print(s2, stdout);

    // vstr_array_t* arr = vstr_array_create(5);
    // vstr_split(arr, s0, ";", NULL, NULL);
    // vstr_array_print(arr, stdout);

    // vstr_free(s0);
    // vstr_free(s2);
    // vstr_array_free(arr);
    int count = 15;
    array_t* arr = new_array(A_TYPE_VALUE, 20, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        put(arr, i, &i);
    }
    int elem;
    for (int i = 0; i < count; i++)
    {
        get(arr, i, &elem);
        printf("%d, ", elem);
    }
    printf("\n\n");
    pop(arr, 5, &elem);
    for (int i = 0; i < count - 1; i++)
    {
        get(arr, i, &elem);
        printf("%d, ", elem);
    }

    return 0;
} 