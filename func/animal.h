#ifndef _ANIMAL_H_
#define _ANIMAL_H_
// публичный интерфейс animal

typedef struct animal_t animal_t;

// аллокатор памяти
animal_t* animal_new();

//конструктор
void animal_ctor(animal_t* animal);

//деструктор
void animal_dtor(animal_t* animal);

//поведенческие функции
void animal_get_name(animal_t* animal, char* name);
void animal_sound(animal_t* animal);



#endif
