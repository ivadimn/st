#ifndef _ROW_H_
#define _ROW_H_

#include <stddef.h>

typedef struct row_t
{
    char **c;
    size_t count;
} row_t;


row_t* new_row(size_t count, size_t max_len);
// void add_data(row_t* row, char* col,  size_t index);
// void get_data(row_t* row, char* col,  size_t index);
// void del_row(row_t* row);


#endif