#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>


#define MAX_PART 8192
typedef enum state { ONE, TWO } state_t;
const uint8_t PERCENT = '%';

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

vstr_t* vstr_create(size_t size);
void vstr_free(vstr_t* str);


static long __inhex(uint8_t ch) {
	const char* hexch = "0123456789ABCDEF";
	for (long i = 0; i < 16; i++)  {
        if ((uint8_t) hexch[i] == ch)
            return i;
    }
    return -1;
}

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

/*
* байты из буфера кладёт в строку
*/
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

/*
* достаёт из строки простые байты и кладёт их в буфер
*/
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
* обнуляет строку
*/
static void __reset(vstr_t* str)
{
    str->bytes = 0;
    str->length = 0;
    for (size_t i = 0; i < str->size; i++)
    {
        str->data[i].utf = 0;
    }
}

/*
* пересчитывает байты в строке
*/
static void __recountbytes(vstr_t* str)
{
    str->bytes = 0;
    for (size_t i = 0; i < str->length; i++)
    {
        str->bytes += (str->data[i].utf < 128) ? 1 : 2;
    }
}

/*
* изменяет размер строки
*/
static void __resize(vstr_t *str, size_t new_size)
{
    elem* new_data = (new_size == 0) ? 
        (elem*)malloc(sizeof(elem) * (str->size * 2)) : (elem*)malloc(sizeof(elem) * new_size);

    memcpy(new_data, str->data, sizeof(elem) * str->length);
    free(str->data);
    str->data = new_data; 
    
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
    fflush(f);
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
* копирование строки или части строки
*/
int vstr_copy(vstr_t* dest, vstr_t* source, size_t start, size_t count)
{
    if ((dest->size < source->length) || (start + count > source->length))
        __resize(dest, source->length * 2);
    
    memcpy(dest->data, &source->data[start], sizeof(elem) * count);
    dest->length = count;
    __recountbytes(dest);
    return 0;    
}

/*
* создаёт объектс vstr из массива символов 
*/
vstr_t* vstr_dup(const char* source) 
{
    size_t len = __str_len((uint8_t*) source);
    vstr_t* dest = vstr_create(len + 1);
    if (dest == NULL)
        return NULL;
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
        vstr_copy(str, left, 0, left->length);
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

    vstr_t* tmp = vstr_dup(s);
    if (str->length < tmp->length)
        return -1;
    
    for (size_t index = 0; index <= str->length - tmp->length; index++) {
        if (memcmp(&str->data[index], tmp->data, tmp->length) == 0)
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

    if (str->length >= str->size)
        __resize(str, 0);
    
    str->bytes += __chartoelem(&(str->data[str->length]), ch);
    str->length++;
    
}

/*
* декодирует url строку в русские буквы
*/
void vstr_urldecode(vstr_t *str) {
    uint8_t buf[4096];
    uint8_t *tmp;
	uint8_t ch;
	state_t state = ONE;
	long index, buf_index = 0;
    int decode = 0;
    size_t len = 0;
    tmp = (uint8_t*)malloc(sizeof(uint8_t) * str->size);

    __datatostr(tmp, str);
    len = strlen((const char*)tmp);

    for (size_t i = 0; i < len; i++) {

		if (tmp[i] == PERCENT) {
            decode = 1;
			continue;
        }
		index = __inhex(tmp[i]);
		if (index >= 0 && decode) {
			switch (state) {
				case ONE:
					ch = hex_val[index];
					ch <<= 4;
					state = TWO;
					break;
				case TWO:
					ch |= hex_val[index];
					state = ONE;
					buf[buf_index++] = ch;
                    decode = 0;
					break;
				default:
					break;
			}
		}
		else {
			buf[buf_index++] = tmp[i];
		}
	}
	buf[buf_index++] = '\0';
    __reset(str);
    vstr_assign(str, (const char*)buf);
    free(tmp);
}

/*
* отсекает часть строки с начала или с конца
*/
void vstr_cut(vstr_t* str, size_t count, int where) {
    size_t index;
    vstr_t* tmp = NULL;
    if (count >= str->length)
        return;
    
    tmp = vstr_create(str->size);
    index = (where == 0) ? 0 : count;
    
    vstr_copy(tmp, str, index, str->length - count);
    
    __reset(str);
    vstr_copy(str, tmp, 0, tmp->length);
    vstr_free(tmp);
}

/*
* заменяет символы в строки на на указанный символ
* если символ 0 то просто удаляет символы из строки
*/
void vstr_replace(vstr_t* str, char* what, uint16_t c)
{
    size_t index = 0;
    vstr_t* tmp = vstr_create(str->length);
    vstr_t* w = vstr_dup(what);

    for (size_t i = 0; i < str->length; i++)
    {
        if (vstr_in(w, str->data[i].utf) >= 0)
        {
            if (c > 0)
                vstr_put_ch(tmp, c);
        }
        else
            vstr_put_ch(tmp, str->data[i].utf);
    }
    vstr_copy(str, tmp, 0, tmp->length);
    vstr_free(tmp);
    vstr_free(w);
}

/*
* переводит строку в нижней регистр
*/
void vstr_tolower(vstr_t* str)
{
    uint16_t ch;
    
    for (size_t i = 0; i < str->length; i++)
    {
        ch = str->data[i].utf;
        if (ch < 128)
        {
            ch = tolower(ch);
            str->data[i].utf = ch;
        }
        else
        {
            ch = str->data[i].utf;
            if (ch >= 0xd090 && ch <= 0xd09f)
            {
                str->data[i].utf = ch + 0x20;    
            }
            else if (ch >= 0xd0a0 && ch <= 0xd0af)
            {
                str->data[i].utf = ch + 0xe0;    
            }
            
            else if (ch == 0xd081) {
                str->data[i].utf = ch + 0x110;    
            }
        }
    }
}

/*
* переводит строку в верхний регистр
*/
void vstr_toupper(vstr_t* str)
{
    uint16_t ch;
    
    for (size_t i = 0; i < str->length; i++)
    {
        ch = str->data[i].utf;
        if (ch < 128)
        {
            ch = toupper(ch);
            str->data[i].utf = ch;
        }
        else
        {
            ch = str->data[i].utf;
            if (ch >= 0xd0b0 && ch <= 0xd0bf)
            {
                str->data[i].utf = ch - 0x20;    
            }
            else if (ch >= 0xd180 && ch <= 0xd18f)
            {
                str->data[i].utf = ch - 0xe0;    
            }
            
            else if (ch == 0xd191) {
                str->data[i].utf = ch - 0x110;    
            }
        }
    }
}

/*
****************************************************************************
* vstr_array functions
*
*****************************************************************************
*/

/*
* скрытая функция изменения размера массива строк 
*/
static int vstr_array_resize(vstr_array_t *arr) {
    // здесь нужно придумать принцип увеличения размера
    // можно использовать время жизни массива и количество увеличений за это время
    long newc = arr->size * 2;
    vstr_t** array = (vstr_t**) malloc(sizeof(vstr_t*) * newc);
    if(array == NULL)
        return -1;
    for (size_t i = 0; i < arr->length; i++)  {
        array[i] = arr->array[i];
    }
    free(arr->array);
    arr->size = newc;
    arr->array = array;
    return 1;
}

/*
* создаёт массив длинной size
*/
vstr_array_t* vstr_array_create(long size) {
    vstr_array_t *arr = (vstr_array_t*) malloc(sizeof(vstr_array_t));
    if (arr == NULL)
        return NULL;
    arr->array = (vstr_t**) malloc(sizeof(vstr_t*) * size);
    if (arr->array == NULL) {
        free(arr);
        return NULL;
    }
    arr->size = size;
    arr->length = 0;
    return arr;
}

/*
* удаляет объект массива и освобождает память
*/
void vstr_array_free(vstr_array_t* arr) {
    for (size_t i = 0; i < arr->length; i++) {
        vstr_free(arr->array[i]);        
    }
    free(arr->array);
    free(arr);
}


/*
* возвращает длину массива
*/
size_t vstr_array_length(vstr_array_t* arr)
{
    return arr->length;
}

/*
* очищает массив
*/
void vstr_array_clear(vstr_array_t* arr) {
    for (size_t i = 0; i < arr->length; i++) {
        free(arr->array[i]);        
    }
    arr->length = 0;
}

/*
* добавляет в массив объект строки vstr_t
*/
size_t vstr_array_addv(vstr_array_t* arr, vstr_t* str) {
    int rc = 0;
    if (arr->length == arr->size) {
        rc = vstr_array_resize(arr);
        if (rc < 0)
            return rc;
    }
    arr->array[arr->length++] = str;
    return arr->length;
}

/*
* добавляет в массив сырую строку
*/
size_t vstr_array_adds(vstr_array_t* arr, const char* str) {
    vstr_t* vstr = vstr_dup(str);
    if(vstr == NULL)
        return -1;

    return vstr_array_addv(arr, vstr);    
}

/*
* возвращает строку по индексу
*/
vstr_t* vstr_array_get(vstr_array_t* arr, size_t index) {
    if (index >= arr->length)
        return NULL;
    return arr->array[index];    
}

/*
* Печатает массив строк в указанный файловый объект
*/
void vstr_array_print(vstr_array_t* arr, FILE* f) {
    for (size_t i = 0; i < arr->length; i++) {
        vstr_print(arr->array[i], f);
    }
}

/*
* соединяет массив строк в одну строку с указанным разделителем
*/
vstr_t* vstr_array_join(vstr_array_t* arr, char* delim) {
    
    vstr_t *str_delim = vstr_dup(delim);
    size_t len_str = 0;

    vstr_t* str = NULL;
    for (size_t i = 0; i < arr->length; i++) {
        len_str += arr->array[i]->length;
    }
    len_str += (str_delim->length * (arr->length - 1));
    
    str = vstr_create(len_str);
    len_str = 0;
    for (size_t i = 0; i < arr->length - 1; i++) {
        memcpy(str->data + len_str, arr->array[i]->data, sizeof(elem) * arr->array[i]->length);
        len_str +=  arr->array[i]->length;
        memcpy(str->data + len_str, str_delim->data, sizeof(elem) * str_delim->length);
        len_str +=  str_delim->length;
    }
    memcpy(str->data + len_str, arr->array[arr->length - 1]->data, 
            sizeof(elem) * arr->array[arr->length - 1]->length);
    len_str += arr->array[arr->length - 1]->length;
    str->length = len_str;
    __recountbytes(str);
    return str;
}