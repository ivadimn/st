#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "animal.h"
#include "animal_p.h"

typedef struct _t
{
    animal_t animal;
} duck_t;

//новое поведение для операции sound
void __duck_sound(void* this_ptr)
{
    animal_t* animal = (animal_t*)this_ptr;
    printf("%s: Quacks\n", animal->name);
}

duck_t* duck_new()
{
    return (duck_t*) malloc(sizeof(duck_t));
}

void duck_ctor(duck_t* duck)
{
    animal_ctor((animal_t*)duck);
    strcpy(duck->animal.name, "Duck");
    //переопределяем  поведенческую функцию sound
    duck->animal.sound_func = __duck_sound;
}

void duck_dtor(duck_t* duck)
{
    animal_dtor((animal_t*) duck);
}