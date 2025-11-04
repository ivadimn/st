#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <stddef.h>
#include <stdint.h>
#include "log.h"
#include "utils.h"


#define REALLOC(ptr, osize, nsize, t)                 \
    do                                                \
    {                                                 \
        t *tmp = (t*)alloc(sizeof(t) * (osize));      \
        memcpy(tmp, ptr, (osize) * sizeof(t));        \
        free(ptr);                                     \
        ptr = (t*) alloc(sizeof(t) * (nsize));        \
        memcpy(ptr, tmp,  (osize) * sizeof(t));       \
        free(tmp);                                    \
    } while(0)                          

typedef enum {
    A_TYPE_VALUE,
    A_TYPE_STRING,
    A_TYPE_POINTER
} atype_t;

typedef struct array_t {
    atype_t type;                       // тип элементов массива
    int *valids;                        // заполненность массива (1 - есть элемент, -1 - нет элемннта)   
    size_t size;                        // размер массива
    size_t size_pointer;                // размер блока данных в массиве
    uint8_t* arr;                       // сам массив данных
} array_t;

/*
* создать новый массив 
* size:         размер массива
* size_pointer: размер блока данных  
*/
array_t* new_array(atype_t type, size_t size, size_t size_pointer);

/*
* удалить массив
*/
void del_array(array_t* arr);

/*
* положить в массив arr эдемент e по индексу index
*/
void put(array_t* arr, size_t index, void* e);

/*
* положить в массив arr другой массив p начиная с индекса index в количестве count
*/
void putm(array_t* arr, size_t index, void* p, size_t count);

/*
* получить элемент массива по индексу
*/
void get(array_t* arr, size_t index, void* e);

/*
* удалить элемент из массива по индексу
*/
void pop(array_t* arr, size_t index, void* e);

#endif
