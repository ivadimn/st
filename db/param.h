#ifndef _PARAM_H_
#define _PARMA_H_

typedef enum {INT, LONG, FLOAT, DOUBLE, CHAR, TEXT, BLOB} type_t;


typedef union value_t
{
    int int_value;
    long long_value;
    float float_value;
    double double_value;
    char char_value;
    char text_value[1024];
    void* blob;
} value_t;






#endif