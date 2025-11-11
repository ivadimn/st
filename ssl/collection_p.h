#ifndef _COLLECTION_P_H_
#define _COLLECTION_P_H_

#include <stddef.h>
#include <stdint.h>


typedef struct collection_t
{
    size_t size;
    size_t size_value;
    uint8_t* items;    
} collection_t;

void _collection_init(collection_t* c, size_t size, size_t size_value);
void _collection_dispose(collection_t* c);

void _collection_add(collection_t* c, size_t index, void* e);
void _collection_move(collection_t* c, size_t index);




#endif