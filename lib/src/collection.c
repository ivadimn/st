#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collection_p.h"
#include "utils.h"

static void __reinit(collection_t* c, size_t new_size)
{
    uint8_t *new_items = (uint8_t*) alloc(sizeof(uint8_t) * (c->size_value * new_size));
    memcpy(new_items, c->items, (c->size_value * c->size));
    free(c->items);
    c->items = new_items;
    c->size = new_size; 
}

size_t _new_size(collection_t* c, size_t index) {
    return c->size + (index * MULT);
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
    if (index >= c->size) {
        size_t new_size = _new_size(c, index);
        __reinit(c, new_size);
    }

    uint8_t* pi = c->items + (index * c->size_value);
    memcpy(pi, e, c->size_value);
}

int _collection_get(collection_t* c, size_t index, void* e)
{
    if (index >= c->size)
        return 1;
    uint8_t* pi = c->items + (index * c->size_value);
    memcpy(e, pi, c->size_value);
    return 0;
}

void _collection_move(collection_t* c, size_t index, size_t count)
{
    if (index >= c->size)
        return;

    uint8_t* dst = c->items + (index * c->size_value);
    uint8_t *src = dst + (count * c->size_value);
        
    memmove(dst, src,  (c->size - (index + count)) * c->size_value);
    dst = c->items + (c->size - count) * c->size_value;
    memset(dst, 0, (c->size_value) * count);    
}

int _collection_has_item(collection_t* c, void* e)
{
    return _collection_index_of(c, e) >= 0 ? 1 : 0;
}

long _collection_index_of(collection_t* c, void* e)
{
    long result = -1;
    uint8_t* pi = c->items, *pe;
    size_t step = c->size_value;
    pe = (uint8_t*) alloc(sizeof(uint8_t) * step);
    for (size_t i = 0; i < c->size; i++)
    {
        memcpy(pe, pi, step);
        if (memcmp(pe, e, step) == 0) {
            result = i;
            break;
        }
        pi += step;
    }
    free(pe);
    return result;
}

