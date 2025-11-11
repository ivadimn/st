#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_info.h"
#include "utils.h"
#include "../lib/src/vstrex.h"
#include "../lib/src/array.h"
#include "dict.h"


const char *line = "80.82.70.140 - - [19/Jul/2020:07:31:03 +0000]  \"GET /%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B HTTP/1.1\" 503 206  \"http://77.244.214.49:80/left.html\" "\
"\"Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:77.0) Gecko/20100101 Firefox/77.0\" \"-\"";
const char *line2 = "Pete Ivanov;250000;ЁНачальник Управления";
const char *url = "%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B";
const char *buf = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const char *buf2 = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

const char* keys[] = {
    "Ключ0",
    "Ключ1",
    "Ключ2",
    "Ключ3",
    "Ключ4",
    "Ключ5",
    "Ключ6",
    "Ключ7",
    "Ключ8",
    "Ключ9"
};

typedef struct data_t {
    char name[32];
    size_t x;
    size_t y;
} data_t;


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
    data_t d;
    dict_t* dict = dict_new(64, 0.72, 2.0, sizeof(data_t));
    for (size_t i = 0; i < 10; i++)
    {
        strcpy(d.name, keys[i]);
        d.x = i * 2;
        d.y = i * 3;
        dict_put(&dict, (unsigned char*)keys[i], &d);
    }

    size_t val = 0;
    for (size_t i = 0; i < 10; i++)
    {
        dict_get(dict, (unsigned char*)keys[i], &d);
        printf("Name: %s, x: %ld, y: %ld\n", d.name, d.x, d.y);
    }
    
    dict_free(dict);

    uint8_t arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    memmove(arr + 2, arr + 3,  8);
    for (size_t i = 0; i < 11; i++)
    {
        printf("%d\n", arr[i]);
    }
    
    
    return 0;
} 