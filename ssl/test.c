#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../lib/src/vstrex.h"
#include "../lib/src/list.h"

const char *line = "80.82.70.140 - - [19/Jul/2020:07:31:03 +0000]  \"GET /%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B HTTP/1.1\" 503 206  \"http://77.244.214.49:80/left.html\" "\
"\"Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:77.0) Gecko/20100101 Firefox/77.0\" \"-\"";
const char *line2 = "Pete Ivanov;250000;ЁНачальник Управления";
const char *url = "%D0%BE%D0%B4%D0%BD%D0%B0%D0%B6%D0%B4%D1%8B";
const char *buf = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const char *buf2 = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

const char* keys[] = {
    "Ключ-0",
    "Ключ-1",
    "Ключ-2",
    "Ключ-3",
    "Ключ-4",
    "Ключ-5",
    "Ключ-6",
    "Ключ-7",
    "Ключ-8",
    "Ключ-9",
    "Ключ-10",
    "Ключ-11",
    "Ключ-12",
    "Ключ-13",
    "Ключ-14",
    "Ключ-15",
    "Ключ-16",
    "Ключ-17",
    "Ключ-18",
    "Ключ-19"
};

typedef struct data_t {
    char name[32];
    size_t x;
    size_t y;
} data_t;

int main(int argc, char** argv)
{
    size_t bcount = 15;
    data_t d;
    list_t* l = list_new(10, sizeof(data_t));

    for (size_t i = 0; i < 20; i++)
    {
        strcpy(d.name, keys[i]);
        d.x = i * 2;
        d.y = i * 3;
        list_add(l, &d);
    }

       
    for (size_t i = 0; i < 20; i++)
    {
        list_get(l, i, &d);
        printf("Name: %s, x: %ld, y: %ld\n", d.name, d.x, d.y);
    }

    list_del(l);
    return 0;
} 