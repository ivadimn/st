#ifndef _CAT_H_
#define _CAT_H_

typedef struct cat_t cat_t;

cat_t* cat_new();

void cat_ctor(cat_t* cat);
void cat_dtor(cat_t* cat);

//поведенческие функции наследуются


#endif