#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>


#define MAX_PART 8192
typedef enum state { ONE, TWO } state_t;

typedef union elem
{
    uint8_t asc[2];
    uint16_t utf;
} elem;


typedef struct {
    elem *data;
    size_t size;                // максимальный длина в символах
    size_t length;              // текущая длина в символах
    size_t bytes;               // текущая длина в байтах
} vstr_t;  

typedef struct {
    vstr_t** array;
    size_t size;
    size_t length;
} vstr_array_t;

const uint8_t hex_val[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};

static long __find(vstr_t* str, uint16_t ch)
{
    elem* data = str->data;
    for (size_t i = 0; i < str->length; i++)
        if (data[i].utf == ch)
            return i;
    return -1;
}

/*
* передача байт из elem в строку uint8_t
*/
static size_t __elemtostr(elem* data, uint8_t* str, size_t index)
{
    if (data->utf < 128)
    {
        str[index++] = data->asc[0];
    }
    else
    {
        str[index++] = data->asc[1];
        str[index++] = data->asc[0];
    }
    return index;
}

/*
* добавление символа с строку
*/
static size_t __chartoelem(elem* data, uint16_t ch)
{
    size_t bytes;
    if (ch < 128)
    {
        data->utf = ch;
        bytes = 1;
    }
    else
    {
        data->asc[1] = (uint8_t)(ch >> 8);
        data->asc[0] = (uint8_t)(ch & 0xFF);
        bytes = 2;
    }
    return bytes;
}

static size_t __str_len(uint8_t* source)
{
    size_t dest_len = 0;
    size_t len = strlen((const char*) source);
    size_t i = 0;

    while (i < len)
    {
        if (source[i] < 128)
        {
            i++;
        }
        else
        {
            i += 2;
        }
        dest_len++;
    }
    return dest_len;
}

static int __strtodata(vstr_t* dest, uint8_t* source, size_t len)
{
    size_t i = 0, index = dest->length;
    elem* data = dest->data;
    size_t lens = __str_len(source);
    if (dest->length + lens > dest->size)
        return -1;
    
    while (i < len)
    {
        if (source[i] < 128)
        {
            data[index++].utf = source[i++];
            dest->bytes++;
        }
        else
        {
            data[index].asc[1] = source[i++];
            data[index++].asc[0] = source[i++];
            dest->bytes += 2;
        }
        dest->length++;    
    }
    return 0;
}


static void __datatostr(uint8_t* dest, vstr_t* source)
{
    size_t index = 0;
    elem* data = source->data;

    for (size_t i = 0; i < source->length; i++)
    {
        if (index < source->bytes)
        {
            if (data[i].utf < 128)
            {
                dest[index++] = data[i].asc[0];
            }
            else
            {
                dest[index++] = data[i].asc[1];
                dest[index++] = data[i].asc[0];
            }
        }
    }
    dest[index] = 0;
}

/*
* создаёт строку размером size
*/
vstr_t* vstr_create(size_t size) {
    vstr_t* str = (vstr_t*) malloc(sizeof(vstr_t));
    if (str == NULL)
        return NULL;
    str->data = (elem*)malloc(sizeof(elem) * (size));
    if (str->data == NULL) {
        free(str);
        return NULL;
    }
    memset(str->data, 0, sizeof(elem) * (size));
    str->size = size;
    str->length = 0;
    str->bytes = 0;
    return str;
}

/*
* уничтожает строку и освоброждает память
*/
void vstr_free(vstr_t* str) {
    free(str->data);
    free(str);
}

/*
* очищает строку заполняя её нулями
*/
void vstr_clear(vstr_t* str) {
    memset(str->data, 0, str->size);
    str->length = 0;
    str->bytes = 0;
}

/*
* напечатать параметры строки
*/
void vstr_print_param(vstr_t* str)
{
    printf("Length - %ld\n", str->length);
    printf("Bytes - %ld\n", str->bytes);
    printf("Size - %ld\n", str->size);
}

/*
* напечатать строку
*/
void vstr_print(vstr_t* str, FILE* f) 
{
    uint8_t* tmp = (uint8_t*) malloc(sizeof(uint8_t) * (str->bytes + 1));
    __datatostr(tmp, str);
    fwrite(tmp, sizeof(uint8_t), strlen((const char*) tmp), f);
    fwrite("\n", 1, 1, f);
    free(tmp);
}

/*
* печатает 16 представление символов в строке
*/
void vstr_print_data(vstr_t* str, FILE* f) 
{
    for (size_t i = 0; i < str->length; i++) {
        fprintf(f, "%x ", str->data[i].utf);
    }
    fprintf(f, "\n");
}

/*
* присваивает созданной уже строке новое значенине
* если выделенный под строку буфер меньше длины новой строки
* то ничего не происходит
*/
void vstr_assign(vstr_t *str, const char* value)
{
    uint8_t* tmp = (uint8_t*) value;
    size_t len = __str_len(tmp);
    if (len < str->size)
        __strtodata(str, tmp, strlen(value));
}

/*
* копирование строки
*/
int vstr_copy(vstr_t* dest, vstr_t* source)
{
    if (dest->size < source->length)
        return -1;
    memcpy(dest->data, source->data, sizeof(elem) * source->length);
    return 0;    
}

/*
* создаёт объектс vstr из массива символов 
*/
vstr_t* vstr_dup(const char* source) 
{
    size_t len = __str_len((uint8_t*) source);
    vstr_t* dest = vstr_create(len + 1);
    __strtodata(dest, (uint8_t*)source, strlen(source));
    return dest;
}

/* сложить строки
* переменное число аргументов char*
* возвращает строку созданную путём сложения входных аргументов 
*/
vstr_t* vstr_plus(long count, ...) {
    long len = 0;
    long len_vals[count];
    va_list ap; 
    vstr_t* str = NULL;  
    uint8_t* tmp;      
    //вычисляем суммарную длину создаваемой строки
    va_start(ap, count);    
    for(long i = 0; i < count; i++)  {
        len_vals[i] = strlen(va_arg(ap, char*));
        len += len_vals[i];
    }
    va_end(ap); 
    tmp = (uint8_t*) malloc(sizeof(uint8_t) * (len + 1));
    if (tmp == NULL)
        return NULL;
        
    va_start(ap, count);  
    len = 0; 
    for(long i = 0; i < count; i++)  {
        memcpy(tmp + len, va_arg(ap, char*), len_vals[i]);
        len +=  len_vals[i];
    }
    va_end(ap); 
    str = vstr_dup((const char*) tmp);
    return str;
}

/*
* возвращает размер буфера для строки
*/
size_t vstr_size(vstr_t* str) {
    return str->size;
}

/*
* возвращает текущую длину строки
*/
size_t vstr_len(vstr_t* str) {
    return str->length;
}

/*
* выполняет конкатенацию двух строк и возвращает новую строку
*/
vstr_t* vstr_concat(vstr_t* left, vstr_t* right) {
    vstr_t *str = vstr_create(left->length + right->length);
    if (str == NULL)
        return NULL;
    memcpy(str->data, left->data, (left->length * sizeof(elem)));
    memcpy(str->data + left->length, right->data, (right->length * sizeof(elem)));
    str->length = left->length + right->length;
    str->bytes = left->bytes + right->bytes;    
    return str;
}

/* добавляет к строке набор байт возвращает новую строкуб старую строку удаляет*/
vstr_t* vstr_append(vstr_t* left, const char* right) {
    vstr_t *str = NULL;

    size_t len_l = left->length;
    size_t len_r = __str_len((uint8_t*)right);
    
    if (len_l + len_r >= left->size) {
        str = vstr_create(len_l + len_r);
        if (str == NULL)
            return NULL;
        vstr_copy(str, left);
        vstr_free(left);
    } else {
        str = left;
    }
    __strtodata(str, (uint8_t*)right, strlen(right));
    return str;
}

/*
* Возвращает индекс вхождения символа в строку или -1
*/
long vstr_in(vstr_t *str, uint16_t ch) {
    return __find(str, ch);
}

/*
* Возвращает символ по заданному индексу или 0
*/
uint16_t vstr_at(vstr_t *str, size_t index) {
    if (index < str->length)
        return str->data[index].utf;
    return 0;    
}

/*
* ищет первое вхождение подстроки в строку и возвращает
* индекс вхождения или -1 если подстрока не найдена  
*/
long vstr_instr(vstr_t *str, char* s) {

    uint8_t* tmp = malloc(sizeof(uint8_t) * (str->bytes + 1));
    size_t lens = __str_len((uint8_t*)s);
    if (str->length < lens)
        return -1;
    
    __datatostr(tmp, str);
    size_t len = strlen(s);
    for (size_t index = 0; index <= str->length - len; index++) {
        if (strncmp((const char*) &tmp[index], s, (size_t) len) == 0)
            return (long)index;
    }
    return -1;
}

/*
* выделяет и возвращает подстроку из строки по индексам
* начала и окончания
*/
vstr_t* vstr_substr(vstr_t *str, long start, long end) {
    long len = end - start;
    vstr_t* substr = NULL;

    if(len < 1)
        return NULL;

    if (start > (long)str->length - 1 || end > (long)str->length)
        return NULL;
           
    substr = vstr_create(len);
    for (long i = 0; i < len; i++) {
        substr->data[i].utf = str->data[start + i].utf;
        substr->bytes += (substr->data[i].utf < 128) ? 1 : 2;
        
    }
    substr->length = len;
    return substr;
}

/*
* разбивает строки на подстроки по разделителю возвращает массив полстрок
* подстроки могут быть сгруппированы символами группировки тогда
* группа включается в массив как подстрока
*/
void vstr_split(/*vstr_array_t* arr,*/ vstr_t* str, char* delim, vstr_t* g_open, vstr_t* g_close) {
    long len = str->length, index = 0;
    elem* buf = str->data;
    uint8_t in_group = 0;
    long g_index = -1;
    int is_delim = 0;
    vstr_t* dlms = vstr_dup(delim);

    uint8_t *part = (uint8_t*) malloc(sizeof(uint8_t) * MAX_PART);
        
    for (long i = 0; i < len; i++) {
        
        switch (in_group)  {
            case 0:
                if (vstr_in(dlms, buf[i].utf) >= 0) {
                    if (!is_delim) {
                        part[index] = '\0';
                        //vstr_array_adds(arr, (char*)part);
                        printf("%s\n", (char*) part);
                        index = 0;
                        is_delim = 1;
                    }
                }
                else {
                    is_delim = 0;
                }

                if(g_open && (g_index = vstr_in(g_open, buf[i].utf)) >= 0) {
                    in_group = 1;
                    is_delim = 1;
                } 
                else if (!is_delim)  {
                    index = __elemtostr(&buf[i], part, index);
                    //part[index++] = buf[i].utf;
                }
                break;
            case 1:
                if (buf[i].utf == vstr_at(g_close, g_index)) {
                    part[index] = 0;
                    //vstr_array_adds(arr, (char*)part);
                    printf("%s\n", (char*) part);
                    index = 0;
                    in_group = 0;
                    g_index = -1;
                }
                else {
                    index = __elemtostr(&buf[i], part, index);
                    //part[index++] = buf[i].utf;
                }
                break;
            default:
                break;
        }

    }
    if (index > 0) {
        part[index] = 0;
        //vstr_array_adds(arr, (char*)part);
        printf("%s\n", (char*) part);    
    }
    vstr_free(dlms);
    free(part);
}


/*
* добавление символа в строку
*/
void vstr_put_ch(vstr_t *str, uint16_t ch) {
    if(str->length < str->size) {
        str->bytes += __chartoelem(&(str->data[str->length]), ch);
        str->length++;
    }
}
