#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>

typedef struct list_t list_t;


list_t* list_new(size_t size, size_t size_value);
void list_del(list_t* l);

/*
* добавить в конец списка
*/
void list_add(list_t* l, void* e);

/*
* добавить в список по индексу
*/
void list_add_by_index(list_t* l, size_t index, void* e);

/*
* удалить элемент из списка
*/
void list_remove(list_t* l, void* e);

/*
* удалить элемент из списка по индексу
*/
void list_remove_by_index(list_t* l, size_t index);

#endif