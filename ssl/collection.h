#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include <stddef.h>

#define DEFAULT_COLLECTION_SIZE     256


typedef void (*operation)(void*);

typedef struct _CollectionClass
{
    operation print;
} CollectionClass;

typedef struct collection_t
{
    CollectionClass *klass;
    size_t size;
    char data[32];
} collection_t;

collection_t* collection_new(size_t size);
void collection_free(collection_t* c);

#endif