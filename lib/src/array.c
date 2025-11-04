#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "utils.h"

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
    arr->valids = (int*) alloc(arr->size * sizeof(int));
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
* сдвигает индексы валидности на 1 влево
*/
static void _move_valid(array_t *arr, size_t index) {

    for (size_t i = index + 1; i < arr->size; i++) {
        arr->valids[i - 1] = arr->valids[i];
    }
}

/*
* распределить память под массив
*/
static void _alloc(array_t* arr) {
    _valid(arr);
    arr->arr = (uint8_t*) alloc(sizeof(uint8_t) * (arr->size * arr->size_pointer));
    memset(arr->arr, 0, (arr->size * arr->size_pointer));
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
}

/*
* создать массив элементов типа t размера size
*/
array_t* new_array(atype_t type, size_t size, size_t size_pointer) {
    array_t *arr = alloc(sizeof(array_t));
    
    arr->valids = NULL;
    arr->size = size;
    arr->type = type;
    arr->size_pointer = size_pointer;
    _alloc(arr);
           
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

void pop(array_t* arr, size_t index, void* e)
{
    uint8_t* cp = arr->arr;
    cp += index * arr->size_pointer;
    if (_isvalid(arr, index)) {
        memcpy(e, cp, arr->size_pointer);
        size_t stay_count = arr->size - (index + 1);
        uint8_t*  rp = cp + arr->size_pointer;
        memcpy(cp, rp, arr->size_pointer * stay_count);
        _move_valid(arr, index);
    }
}
