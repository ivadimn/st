#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//base
//    TypeA
//    TypeB
//    TypeC

/*#define DECLARE_FUN(type)   elem_t create_##type(Type, type)
#define DEFINE_FUN(type)    elem_t create_##type(Type t, type val)  \
{                                                                   \
    elem_t val;                                                     \
                                                                    \
} */                                                                  

typedef enum
{
    BASE_TYPE,
    TYPE_A,
    TYPE_B,
    TYPE_C
} Type;

/*typedef union value_t
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
} elem_t; */


typedef struct 
{
    Type type;
} Base;

typedef struct 
{
    Type type;
    char* str;
} TypeA;

typedef struct 
{
    Type type;
    double dbl;
} TypeB;

typedef struct 
{
    Type type;
    int ival;
} TypeC;


typedef union 
{
    Base base;
    TypeA type_a;
    TypeB type_b;
    TypeC type_c;
} Object;


//DECLARE_FUN(int);

int 
main(int argc, char** argv)
{
    Object obj;

    obj.base.type = TYPE_A;
    obj.type_a.str = "type a";

    printf("obj type: %d\n", obj.base.type);
    printf("obj type_a type : %d\n", obj.type_a.type);
    printf("obj value: %s\n", obj.type_a.str);
    printf("size of long: %ld\n", sizeof(long));

    return 0;
}


