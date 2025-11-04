#include "row.h"
#include "../lib/src/utils.h"


row_t* new_row(size_t count, size_t max_len)
{
    row_t* row = (row_t*) alloc(sizeof(row_t));
    row->c = (char**) alloc(sizeof(char*) * count);
    for (size_t i = 0; i < count; i++)
    {
        row->c[i] = (char*) alloc(sizeof(char) * max_len);
    }
       
    row->count = count;
    return row;
}
// void add_data(row_t* row, char* col,  size_t index);
// void get_data(row_t* row, char* col,  size_t index);
// void del_row(row_t* row);

// row_t* new_row(size_t count, atype_t type, size_t size_pointer)
// {
//     row_t* row = (row_t*) alloc(sizeof(row_t));
//     row->data = new_array(type, count, size_pointer);
//     row->count = count;
//     return row;
// }
// void add_data(row_t* row,  size_t index, void* e)
// {
//     put(row->data, index, e);
//     printf("\t--%p\n", e);
// }
// void get_data(row_t* row,  size_t index, void* e)
// {
//     get(row->data, index, e);
// }
// void del_row(row_t* row)
// {
//     del_array(row->data);
//     free(row);
// }
