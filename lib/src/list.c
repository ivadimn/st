#include <stdlib.h>
#include <stddef.h>
#include "collection_p.h"
#include "utils.h"

typedef struct list_t {
    collection_t c;
    size_t length;
} list_t;


list_t* list_new(size_t size, size_t size_value)
{
    list_t* l = (list_t*) alloc(sizeof(list_t));
    _collection_init(&l->c, size, size_value);
    l->length = 0;
    return l; 
} 
void list_del(list_t* l)
{
    _collection_dispose(&l->c);
    free(l);
}

/*
* добавить в конец списка
*/
void list_add(list_t* l, void* e)
{
    _collection_add(&l->c, l->length, e);
    l->length++;
}

/*
* добавить в список по индексу
*/
void list_add_by_index(list_t* l, size_t index, void* e)
{
    if (index >= l->length)
        return;
    _collection_add(&l->c, index, e);
}

/*
* получить элемент по индексу
*/
int list_get(list_t* l, size_t index, void* e)
{
    if (index >= l->length)
        return 1;    
    return _collection_get(&l->c, index, e);
}
    


/*
* удалить элемент из списка по индексу
*/
void list_remove_by_index(list_t* l, size_t index)
{
    if (index >= 0 && index < l->length) 
    {
        _collection_move(&l->c, index, 1);
        l->length--;
    }   
}

/*
* удалить элемент из списка
*/
void list_remove(list_t* l, void* e)
{
    long index = _collection_index_of(&l->c, e);
    if (index >= 0)
        list_remove_by_index(l, (size_t) index);       
}

/*
* получить длину списка
*/
size_t list_length(list_t* l)
{
    return l->length;
}


