#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collection_p.h"
#include "utils.h"

#define MULT    2

static void __reinit(collection_t* c, size_t new_size)
{
    uint8_t *new_items = (uint8_t*) alloc(sizeof(uint8_t) * (c->size_value * new_size));
    memcpy(new_items, c->items, (c->size_value * c->size));
    c->size = new_size; 
}

void _collection_init(collection_t* c, size_t size, size_t size_value)
{
    c->size = size;
    c->size_value = size_value;
    c->items = (uint8_t*) alloc(sizeof(uint8_t) * (c->size_value * c->size));
}
void _collection_dispose(collection_t* c)
{
    if (c->items)
        free(c->items);    
}

void _collection_add(collection_t* c, size_t index, void* e)
{
    if (index >= c->size)
        __reinit(c, c->size * MULT);

    uint8_t* pi = c->items + (index * c->size_value);
    memcpy(pi, e, c->size_value);
}

void _collection_move(collection_t* c, size_t index)
{
    if (index >= c->size)
        return;

    uint8_t* pi = c->items + (index * c->size_value);
    memset(pi, 0, c->size_value);    
}


