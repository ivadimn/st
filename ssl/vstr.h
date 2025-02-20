#ifndef _VSTR_H_
#define _VSTR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_PART 8192
typedef enum state { ONE, TWO } state_t;


typedef struct {
    uint8_t *data;
    long size;
    long length;
} vstr_t;  

typedef struct {
    vstr_t** array;
    long size;
    long length;
} vstr_array_t;


/*
* создать строку
* size - максимальная длина строки
*/

vstr_t* vstr_create(long size);
/*
* уничтожить строку  
*/
void vstr_free(vstr_t* str);

/* сложить строки
* переменное число аргументов char*
*/
vstr_t* vstr_plus(long count, ...);

/*
* очищает строку заполняя её нулями
*/
void vstr_clear(vstr_t* str);

/*
* возвращает размер буфера для строки
*/
size_t vstr_size(vstr_t* str);

/*
* возвращает текущую длину строки
*/
size_t vstr_len(vstr_t* str);

/*
* напечатать строку
*/
void vstr_print(vstr_t* str, FILE* f);

/*
* печатает 16 представление символов в строке
*/
void vstr_print_data(vstr_t* str, FILE* f);

/*
* присваивает созданной уже строке новое значенине
* если выделенный под строку буфер меньше длины новой строки
* то ничего не происходит
*/
void vstr_assign(vstr_t *str, const char* value);

/*
* создаёт объектс vstr из массива символов 
*/
vstr_t* vstr_dup(const char* source);

/*
* выполняет конкатенацию двух строк и возвращает новую строку
*/
vstr_t* vstr_concat(vstr_t* left, vstr_t* right);

/* добавляет к строке набор байт возвращает новую строкуб старую строку удаляет*/
vstr_t* vstr_append(vstr_t* left, const char* right);


/*
* разбивает строку на массив строк по разделителю, с учётом группировки 
* если часть строки сгруппирована, то символы разделителя там не работают
* и выделяется группа целиком
*/
void vstr_split(vstr_array_t* arr, vstr_t* str, char* delim, vstr_t* g_open, vstr_t* g_close);
void vstr_split1(vstr_array_t* arr, vstr_t* str, char* delim, vstr_t* g_open, vstr_t* g_close);

/*
* Возвращает индекс вхождения символа в строку или -1
*/
long vstr_in(vstr_t *str, char ch);

/*
* ищет первое вхождение подстроки в строку и возвращает
* индекс вхождения или -1 если подстрока не найдена  
*/
long vstr_instr(vstr_t *str, char* s);
vstr_t* vstr_substr(vstr_t *str, long start, long end);

/*
* Возвращает символ по заданному индексу или 0
*/
uint8_t vstr_at(vstr_t *str, long index);


void vstr_put_ch(vstr_t *str, char ch);
void vstr_urldecode(vstr_t *str);
void vstr_cut(vstr_t* str, long count, int where);

vstr_array_t* vstr_array_create(long size);
void vstr_array_free(vstr_array_t* arr);
void vstr_array_clear(vstr_array_t* arr);
long vstr_array_addv(vstr_array_t* arr, vstr_t* str);
long vstr_array_adds(vstr_array_t* arr, const char* str);
vstr_t* vstr_array_get(vstr_array_t* arr, long index);
vstr_t* vstr_array_join(vstr_array_t* arr, char* delim);
void vstr_array_print(vstr_array_t* arr, FILE* f);
#endif
