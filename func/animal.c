#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal_p.h"

//родительское определение animal_sound, которое используется по умолчанию
void __animal_sound(void* this_ptr)
{
    animal_t* animal = (animal_t*)this_ptr;
    printf("%s: Beeeep\n", animal->name);
}

animal_t* animal_new() 
{
    return (animal_t*) malloc(sizeof(animal_t));
}

//конструктор
void animal_ctor(animal_t* animal)
{
    animal->name = (char*) malloc(10 * sizeof(char));
    strcpy(animal->name, "Animal");
    animal->sound_func = __animal_sound;
}

//деструктор
void animal_dtor(animal_t* animal)
{
    free(animal->name);
}

//поведенческие функции
void animal_get_name(animal_t* animal, char* name)
{
    strcpy(name, animal->name);
}


void animal_sound(animal_t* animal)
{
    animal->sound_func(animal);
}


