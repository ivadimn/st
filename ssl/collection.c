#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collection.h"
#include "utils.h"


static void __print(void* c)
{
    collection_t *col = (collection_t*) c;
    printf("%s\n", col->data);
}


collection_t* collection_new(size_t size) {
    collection_t *c = (collection_t *) alloc(sizeof(collection_t));
    c->klass = (CollectionClass*) alloc(sizeof(CollectionClass));
    c->klass->print = __print;
    strcpy(c->data,"Any data");
}

void collection_free(collection_t* c) {

}
