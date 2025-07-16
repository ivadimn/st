#ifndef _ANIMAL_P_H_
#define _ANIMAL_P_H_

//тип указателя на функцию, необходимого для обращения к разным версиям animal_sound
typedef void (*sound_func_t)(void*);

typedef struct animal_t 
{
    char *name;
    //указатель на функцию, которая отвечает за вывод звуков
    sound_func_t sound_func;
} animal_t;




#endif