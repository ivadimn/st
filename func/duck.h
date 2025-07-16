#ifndef _DUCK_H_
#define _DUCK_H_

typedef struct duck_t duck_t;

duck_t* duck_new();

void duck_ctor(duck_t* cat);
void duck_dtor(duck_t* cat);

//поведенческие функции наследуются


#endif