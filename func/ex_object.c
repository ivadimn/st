#include <stdio.h>
#include <stdint.h>

//base
//    TypeA
//    TypeB
//    TypeC

#define DECLARE_FUN(type)   elem_t create_##type(Type, type)
#define DEFINE_FUN(type)    elem_t create_##type(Type t, type val)  \
{                                                                   \
    elem_t val;                                                     \
                                                                    \
}                                                                   

typedef enum
{
    TYPE_8,
    TYPE_U8,
    TYPE_16,
    TYPE_U16
} Type;

typedef union value_t
{
    int8_t val8;
    uint8_t valu8;
    int16_t val16;
    uint16_t valu16;
} value_t;

typedef struct elem_t
{
    Type type;
    value_t val;
} elem_t;


typedef struct 
{
    int dummy;
} Base;

typedef struct 
{
    char* str;
} TypeA;

typedef struct 
{
    double dbl;
} TypeB;

typedef struct 
{
    int ival;
} TypeC;


typedef union 
{
    Base base;
    TypeA type_a;
    TypeB type_b;
    TypeC type_c;
} Object;


DECLARE_FUN(int);

int 
main(int argc, char** argv)
{
    Object obj;

    obj.type_b.dbl = 250.456;

    printf("type_c = %d\n", obj.type_c.ival);

    return 0;
}


