#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person_p.h"

void get_first_name(person_t* person, char* buf)
{
    strncpy(buf, person->first_name, NAME_LEN -1);    
}

void get_second_name(person_t* person, char* buf)
{
    strncpy(buf, person->secong_name, NAME_LEN -1);
}

void get_surname(person_t* person, char* buf)
{
    strncpy(buf, person->surname, NAME_LEN -1);
}

void get_birthday(person_t* person, birthday_t* birthday)
{
    memcpy(birthday, &(person->birthday), sizeof(birthday_t));
}

void set_first_name(person_t* person, char* buf)
{
    strncpy(person->first_name, buf, NAME_LEN -1);    
}

void set_second_name(person_t* person, char* buf)
{
    strncpy(person->secong_name, buf, NAME_LEN -1);
}

void set_surname(person_t* person, char* buf)
{
    strncpy(person->surname, buf, NAME_LEN -1);
}

void set_birthday(person_t* person, birthday_t* birthday)
{
    memcpy(&(person->birthday), birthday, sizeof(birthday_t));
}

void set_birthday_raw(person_t* person, char* buf)
{
    sscanf(buf, "%d-%d-%d", &(person->birthday.year), 
                            &(person->birthday.month),
                            &(person->birthday.day));
}

void print_person(person_t* person)
{
    char buf[NAME_LEN * 3 + DATE_LEN];
    snprintf(buf, NAME_LEN * 3 + DATE_LEN, "%s %s %s %d.%d.%d",
                                            person->first_name,
                                            person->secong_name,
                                            person->surname,
                                            person->birthday.day,
                                            person->birthday.month,
                                            person->birthday.year
                                            );
    printf("%s\n", buf);
    
}