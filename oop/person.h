#ifndef _PERSON_H_
#define _PERSON_H_

#include "db_type.h"

typedef struct person_t person_t;

person_t* new_person();
void init_person(person_t* person, char* fname, char* sname, char* surname, char* birthday); 
void del_person(person_t* person);

void get_first_name(person_t* person, char* buf);
void get_second_name(person_t* person, char* buf);
void get_surname(person_t* person, char* buf);
void get_birthday(person_t* person, birthday_t* birthday);

void set_first_name(person_t* person, char* buf);
void set_second_name(person_t* person, char* buf);
void set_surname(person_t* person, char* buf);
void set_birthday(person_t* person, birthday_t* birthday);
void set_birthday_raw(person_t* person, char* buf);

void print_person(person_t* person);
void format_birthday(person_t* person);



#endif