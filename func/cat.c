#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "animal.h"
#include "animal_p.h"

typedef struct _t
{
    animal_t animal;
} cat_t;

//новое поведение для операции sound
void __cat_sound(void* this_ptr)
{
    animal_t* animal = (animal_t*)this_ptr;
    printf("%s: Meow\n", animal->name);
}

cat_t* cat_new()
{
    return (cat_t*) malloc(sizeof(cat_t));
}

void cat_ctor(cat_t* cat)
{
    animal_ctor((animal_t*)cat);
    strcpy(cat->animal.name, "Cat");
    //переопределяем  поведенческую функцию sound
    cat->animal.sound_func = __cat_sound;
}

void cat_dtor(cat_t* cat)
{
    animal_dtor((animal_t*) cat);
}
