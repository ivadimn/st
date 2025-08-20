#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

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
    arr->valids = (int*) malloc(arr->size * sizeof(int));
    if(arr->valids == NULL)
        crit("Ошибка распределения памяти для массива валидаторов\n");
    for (size_t i = 0; i < arr->size; i++) {
        arr->valids[i] = -1;
    }
}

/*
* расширяет размерность массива валидаторов
*/
static void _revalid(array_t *arr, size_t index) {

    size_t old_size = arr->size;
    size_t new_size = arr->size+index;

    REALLOC(arr->valids, old_size, new_size, int);

    for (size_t i = arr->size; i < arr->size + index; i++) {
        arr->valids[i] = -1;
    }
}

/*
* распределить память под массив
*/
static void _alloc(array_t* arr) {
    _valid(arr);
    arr->arr = (uint8_t*) calloc(arr->size * arr->size_pointer,  sizeof(uint8_t));
    if(arr->arr == NULL)
        crit("Ошибка распределения памяти для элементов массива\n");
}


/*
* расширить размерность массива
*/
static void _realloc(array_t* arr, size_t index) {
    _revalid(arr, index);
    size_t osize = arr->size * arr->size_pointer;
    size_t nsize = (arr->size+index) * arr->size_pointer;
    REALLOC(arr->arr, osize, nsize, uint8_t);
    arr->size += index;
  
    
}
/*
* расширить размерность массива
*/
static void _renew(array_t* arr, size_t index) {

    _realloc(arr, index); 
    if (arr->arr == NULL) 
        crit("Ошибка распределения памяти при изменение размера массива");
}

/*
* создать массив элементов типа t размера size
*/
array_t* new_array(atype_t type, size_t size, size_t size_pointer) {
    array_t *arr = malloc(sizeof(array_t));
    if (arr == NULL) 
        crit("Ошибка распределения памяти под массив");

    arr->valids = NULL;
    arr->size = size;
    arr->type = type;
    arr->size_pointer = size_pointer;
    _alloc(arr);
   
    if (arr->arr == NULL) 
        crit("Ошибка распределения памяти под элементы массива");
        
    return arr;
}
/*
* удалить массив
*/
void del_array(array_t* arr) {
    if (arr) {
        if(arr->arr)
            free(arr->arr);
        if (arr->valids) {
            free(arr->valids);
        }
        free(arr);    
    }
}

/*
* положить в массив элемент e по индексу index
*/
void put(array_t* arr, size_t index,  void* e) {

    uint8_t* cp = NULL;
    if(index >= arr->size) {
        _renew(arr, index);
    }
    cp = arr->arr + (index * arr->size_pointer); 
    memcpy(cp, e, arr->size_pointer);
    arr->valids[index] = index;
    
}

/*
* положить в массив arr другой массив p начиная с индекса index в количестве count
*/
void putm(array_t* arr, size_t index, void* p, size_t count) {
    uint8_t* cp = NULL;
    size_t last_index = index + count;
    if(last_index >= arr->size) {
        _renew(arr, last_index);
    }
    cp = arr->arr + (index * arr->size_pointer);
    memcpy(cp, p, (arr->size_pointer * count));
    for (size_t i = index; i < index + count; i++) {
        arr->valids[i] = i;
    }
}
/*
* получить элемент массива по индексу
*/
void get(array_t* arr, size_t index,  void* e) {
    uint8_t* cp = arr->arr;
    cp += index * arr->size_pointer;
    if (_isvalid(arr, index)) {
        memcpy(e, cp, arr->size_pointer);
    }
}