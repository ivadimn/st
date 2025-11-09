#ifndef _DICT_H_
#define _DICT_H_

#include <stddef.h>
#include <stdint.h>

#define CELL_CMP_EQ(a, b)  (strcmp((char*)(a), (char*)(b)) == 0)
typedef unsigned char alpha;

typedef enum {CHAR, INT, LONG, FLOAT, DOUBLE, STR } val_type_t;

typedef struct cell_t {
    alpha* key;
    uint8_t* value;
} cell_t;

typedef struct dict_t {
    cell_t **data;          //данные
    size_t count;           //сколько уже заполнено
    size_t size;            //всего элементов массива
    size_t limit;           //если элементов больше чем лимит пересоздаём dict
    float factor;           //степень заполнения массива по
                            //достижении которого пересоздётся dict
    float mult;             //во столько раз увеличится размер dict
    size_t size_value;    // тип значения ключа
} dict_t;


dict_t* dict_new(size_t size, float factor, float mult, size_t size_value);
void dict_free(dict_t* dict);

dict_t* dict_renew(dict_t ** , cell_t*);
void dict_put(dict_t**, alpha*, void*);
void dict_get(dict_t *dict, alpha* word, void* e);
void print_dict_st(dict_t*);
void print_dict(dict_t* );

unsigned long long hash_code(alpha* word);

#endif
