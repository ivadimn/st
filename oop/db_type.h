#ifndef _DB_TYPE_H_
#define _DB_TYPE_H_

#include "const.h"

typedef struct birthday_t
{
    unsigned char day;
    unsigned char month;
    unsigned short year;
    char str[DATE_LEN];
} birthday_t;

#endif