#ifndef _VSTREX_H_
#define _VSTREX_H_

#include <stdio.h>
#include <stdint.h>

#define FROM_START  1
#define FROM_END    0

typedef union elem
{
    uint8_t asc[sizeof(int)];
    int utf;
} elem;


typedef struct vstr_t vstr_t;  

typedef struct vstr_array_t vstr_array_t;


/*
* создать строку
* size - максимальная длина строки
*/
vstr_t* vstr_create(size_t size);
/*
* уничтожить строку  
*/
void vstr_free(vstr_t* str);

/*
* очищает строку заполняя её нулями
*/
void vstr_clear(vstr_t* str);

/*
* присваивает созданной уже строке новое значенине
* если выделенный под строку буфер меньше длины новой строки
* то ничего не происходит
*/
void vstr_assign(vstr_t *str, const char* value);

/*
* копирование строки
*/
int vstr_copy(vstr_t* dest, vstr_t* source);

/*
* создаёт объектс vstr из массива символов 
*/
vstr_t* vstr_dup(const char* source);

/*
* напечатать параметры строки
*/
void vstr_print_param(vstr_t* str);

/*
* напечатать строку
*/
void vstr_print(vstr_t* str, FILE* f);

/*
* печатает 16 представление символов в строке
*/
void vstr_print_data(vstr_t* str, FILE* f);

/* сложить строки
* переменное число аргументов char*
* возвращает строку созданную путём сложения входных аргументов 
*/
vstr_t* vstr_plus(long count, ...);

/*
* возвращает размер буфера для строки
*/
size_t vstr_size(vstr_t* str);

/*
* возвращает текущую длину строки
*/
size_t vstr_len(vstr_t* str);

/*
* выполняет конкатенацию двух строк и возвращает новую строку
*/
vstr_t* vstr_concat(vstr_t* left, vstr_t* right);

/* добавляет к строке набор байт возвращает новую строкуб старую строку удаляет*/
vstr_t* vstr_append(vstr_t* left, const char* right);

/*
* Возвращает индекс вхождения символа в строку или -1
*/
long vstr_in(vstr_t *str, uint16_t ch);

/*
* Возвращает символ по заданному индексу или 0
*/
uint16_t vstr_at(vstr_t *str, size_t index);

/*
* ищет первое вхождение подстроки в строку и возвращает
* индекс вхождения или -1 если подстрока не найдена  
*/
long vstr_instr(vstr_t *str, char* s);

/*
* выделяет и возвращает подстроку из строки по индексам
* начала и окончания
*/
vstr_t* vstr_substr(vstr_t *str, long start, long end);

/*
* разбивает строки на подстроки по разделителю возвращает массив полстрок
* подстроки могут быть сгруппированы символами группировки тогда
* группа включается в массив как подстрока
*/
void vstr_split(/*vstr_array_t* arr,*/ vstr_t* str, char* delim, vstr_t* g_open, vstr_t* g_close);

/*
* добавление символа в строку
*/
void vstr_put_ch(vstr_t *str, uint16_t ch);

/*
* декодирует url строку в русские буквы
*/
void vstr_urldecode(vstr_t *str);

/*
* отсекает часть строки с начала или с конца
*/
void vstr_cut(vstr_t* str, size_t count, int where);

/*
* заменяет символы в строки на на указанный символ
* если символ 0 то просто удаляет символы из строки
*/
void vstr_replace(vstr_t* str, char* what, uint16_t c);

/*
* переводит строку в нижней регистр
*/
void vstr_tolower(vstr_t* str);

/*
* переводит строку в верхний регистр
*/
void vstr_toupper(vstr_t* str);


/*
* функции для работы с массивом строк
*/

/*
* создаёт массив длинной size
*/
vstr_array_t* vstr_array_create(size_t size);

/*
* удаляет объект массива и освобождает память
*/
void vstr_array_free(vstr_array_t* arr);

/*
* возвращает длину массива
*/
size_t vstr_array_length(vstr_array_t* arr);

/*
* очищает массив
*/
void vstr_array_clear(vstr_array_t* arr);

/*
* добавляет в массив объект строки vstr_t
*/
size_t vstr_array_addv(vstr_array_t* arr, vstr_t* str);

/*
* добавляет в массив сырую строку
*/
size_t vstr_array_adds(vstr_array_t* arr, const char* str);

/*
* возвращает строку по индексу
*/
vstr_t* vstr_array_get(vstr_array_t* arr, size_t index);

/*
* Печатает массив строк в указанный файловый объект
*/
void vstr_array_print(vstr_array_t* arr, FILE* f);

/*
* соединяет массив строк в одну строку с указанным разделителем
*/
vstr_t* vstr_array_join(vstr_array_t* arr, char* delim);

#endif