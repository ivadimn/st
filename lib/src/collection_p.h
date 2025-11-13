#ifndef _COLLECTION_P_H_
#define _COLLECTION_P_H_

#include <stddef.h>
#include <stdint.h>

#define MULT    2

typedef struct collection_t
{
    size_t size;
    size_t size_value;
    uint8_t* items;    
} collection_t;

size_t _new_size(collection_t* c, size_t index);
void _collection_init(collection_t* c, size_t size, size_t size_value);
void _collection_dispose(collection_t* c);

void _collection_add(collection_t* c, size_t index, void* e);
int _collection_get(collection_t* c, size_t index, void* e);
void _collection_move(collection_t* c, size_t index, size_t count);
int _collection_has_item(collection_t* c, void* e);
long _collection_index_of(collection_t* c, void* e);




#endif