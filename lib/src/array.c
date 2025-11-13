#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "collection_p.h"
#include "array.h"
#include "utils.h"

typedef struct array_t {
    collection_t c;    
    int *valids;                        // заполненность массива (1 - есть элемент, -1 - нет элемннта)   
} array_t;

/*
* проверяет наличие элемента в массиве arr по индексу index
* возвращает 1 если есть элемент 0 если нет элемента
*/
static int _isvalid(array_t *arr, size_t index) {
    return 1 ? arr->valids[index] >= 0 : 0;
}

/*
* создаёт массив валидаторов и заполняет его -1 
* все элемннты свободны
*/
static void _valid(array_t *arr) {
    arr->valids = (int*) alloc(arr->c.size * sizeof(int));
    for (size_t i = 0; i < arr->c.size; i++) {
        arr->valids[i] = -1;
    }
}
/*
* расширяет размерность массива валидаторо
*/
static void __revalid(array_t *arr, size_t index) {

    size_t old_size = arr->c.size;
    size_t new_size = _new_size(&arr->c, index);
    int* tmp = (int*) alloc(sizeof(int) * old_size);
    memcpy(tmp, arr->valids, sizeof(int) * old_size);
    free(arr->valids);
    arr->valids = (int*) alloc(sizeof(int) * new_size);
    memcpy(arr->valids, tmp, sizeof(int) * old_size);
    free(tmp);
    for (size_t i = old_size; i < new_size; i++) {
        arr->valids[i] = -1;
    }
}
/*
* создать новый массив 
* size:         размер массива
* size_pointer: размер блока данных  
*/
array_t* array_new(size_t size, size_t size_value)
{
    array_t *arr = alloc(sizeof(array_t));
    arr->valids = NULL;
    _collection_init(&arr->c, size, size_value), 
    _valid(arr);
           
    return arr;    
}
/*
* удалить массив
*/
void array_del(array_t* arr)
{
    _collection_dispose(&arr->c);
    free(arr->valids);
    free(arr);
}
/*
* положить в массив arr эдемент e по индексу index
*/
void array_add(array_t* arr, size_t index, void* e)
{
    if (index >= arr->c.size)
        __revalid(arr, index);
    _collection_add(&arr->c, index, e);
    arr->valids[index] = 1;
}

/*
* положить в массив arr другой массив p начиная с индекса index в количестве count
*/
void array_addm(array_t* arr, size_t index, void* p, size_t count)
{

}

/*
* получить элемент массива по индексу
*/
int array_get(array_t* arr, size_t index, void* e)
{
    if (index >= arr->c.size || !_isvalid(arr, index))
        return 1;
    return _collection_get(&arr->c, index, e);
}

/*
* удалить элемент из массива по индексу
*/
void array_remove(array_t* arr, size_t index)
{
    if (index >= arr->c.size)
        return;
    arr->valids[index] = -1;    
}
