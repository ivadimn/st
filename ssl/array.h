#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <stddef.h>
#include <stdint.h>
#include "log.h"
#include "utils.h"

typedef struct array_t  array_t;

/*
* создать новый массив 
* size:         размер массива
* size_pointer: размер блока данных  
*/
array_t* array_new(size_t size, size_t size_value);

/*
* удалить массив
*/
void array_del(array_t* arr);

/*
* положить в массив arr эдемент e по индексу index
*/
void array_add(array_t* arr, size_t index, void* e);

/*
* положить в массив arr другой массив p начиная с индекса index в количестве count
*/
void array_addm(array_t* arr, size_t index, void* p, size_t count);

/*
* получить элемент массива по индексу
*/
int array_get(array_t* arr, size_t index, void* e);

/*
* удалить элемент из массива по индексу
*/
void array_remove(array_t* arr, size_t index);

#endif
