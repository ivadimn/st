#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_PART 8192
typedef enum state { ONE, TWO } state_t;

typedef struct {
    uint8_t *data;
    long size;
    long length;
} vstr_t;  

typedef struct {
    vstr_t** array;
    long size;
    long length;
} vstr_array_t;




const uint8_t hex_val[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};

static long inhex(uint8_t ch) {
	const char* hexch = "0123456789ABCDEF";
	for (long i = 0; i < 16; i++)  {
        if ((uint8_t) hexch[i] == ch)
            return i;
    }
    return -1;
}

/*
* создаёт строку размером size
*/
vstr_t* vstr_create(long size) {
    vstr_t* str = (vstr_t*) malloc(sizeof(vstr_t));
    if (str == NULL)
        return NULL;
    str->data = (uint8_t*)malloc(sizeof(uint8_t) * (size + 1));
    if (str->data == NULL) {
        free(str);
        return NULL;
    }
    memset(str->data, 0, sizeof(uint8_t) * (size + 1));
    str->size = size + 1;
    str->length = 0;
    return str;
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
    //вычисляем суммарную длину создаваемой строки
    va_start(ap, count);    
    for(long i = 0; i < count; i++)  {
        len_vals[i] = strlen(va_arg(ap, char*));
        len += len_vals[i];
    }
    va_end(ap); 
    str = vstr_create(len);
    va_start(ap, count);  
    len = 0; 
    for(long i = 0; i < count; i++)  {
        memcpy(str->data + len, va_arg(ap, char*), len_vals[i]);
        len +=  len_vals[i];
    }
    va_end(ap); 
    str->data[len] = '\0'; 
    str->length = len;
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
* напечатать строку
*/
void vstr_print(vstr_t* str, FILE* f) {
    fwrite(str->data, sizeof(uint8_t), str->length, f);
    fwrite("\n", 1, 1, f);
}

/*
* печатает 16 представление символов в строке
*/
void vstr_print_data(vstr_t* str, FILE* f) {
    for (long i = 0; i < str->length; i++) {
        fprintf(f, "%x ", str->data[i]);
    }
    fprintf(f, "\n");
}

/*
* присваивает созданной уже строке новое значенине
* если выделенный под строку буфер меньше длины новой строки
* то ничего не происходит
*/
void vstr_assign(vstr_t *str, const char* value) {
    uint8_t* tmp = (uint8_t*) value;
    long len = strlen(value);
    if (len < str->size) {
        memcpy(str->data, tmp, len);
        str->data[len] = 0;
        str->length = len;
    }
}

/*
* создаёт объектс vstr из массива символов 
*/
vstr_t* vstr_dup(const char* source) {
    size_t len = strlen(source);
    vstr_t* dest = vstr_create(len);
    if (dest) { 
        memcpy(dest->data, source, len);
        dest->length = len;
    }    
    return dest;
}

/*
* выполняет конкатенацию двух строк и возвращает новую строку
*/
vstr_t* vstr_concat(vstr_t* left, vstr_t* right) {
    vstr_t *str = vstr_create(left->length + right->length);
    if (str == NULL)
        return NULL;
    memcpy(str->data, left->data, left->length);
    memcpy(str->data + left->length, right->data, right->length);
    str->length = left->length + right->length;
    str->data[str->length] = 0;
    return str;
}


/* добавляет к строке набор байт возвращает новую строкуб старую строку удаляет*/
vstr_t* vstr_append(vstr_t* left, const char* right) {
    vstr_t *str = NULL;
    long len_r = strlen(right);
    long len_l = left->length;
    if (len_l + len_r >= left->size) {
        str = vstr_create(len_l + len_r);
        if (str == NULL)
            return NULL;
        memcpy(str->data, left->data, len_l);
        vstr_free(left);
    } else {
        str = left;
    }
    memcpy(str->data + len_l, right, len_r);
    str->length = len_l + len_r;
    str->data[str->length] = 0;
    return str;
}

/*
* Возвращает индекс вхождения символа в строку или -1
*/
long vstr_in(vstr_t *str, char ch) {
    for (long i = 0; i < str->length; i++)  {
        if (str->data[i] == ch)
            return i;
    }
    return -1;
}

/*
* Возвращает символ по заданному индексу или 0
*/
uint8_t vstr_at(vstr_t *str, long index) {
    if (index < str->length)
        return str->data[index];
    return 0;    
    
}

/*
* ищет первое вхождение подстроки в строку и возвращает
* индекс вхождения или -1 если подстрока не найдена  
*/
long vstr_instr(vstr_t *str, char* s) {
    char* tmp = (char*)str->data;
    long len = (long)strlen(s);
    if (str->length < len)
        return -1;
    
    for (long index = 0; index <= str->length - len; index++) {
        if (strncmp(&tmp[index], s, (size_t) len) == 0)
            return index;
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

    if (start > str->length - 1 || end > str->length)
        return NULL;
           
    substr = vstr_create(len);
    for (long i = 0; i < len; i++) {
        substr->data[i] = str->data[start + i];
    }
    substr->length = len;
    substr->data[len] = '\0';
    return substr;
}

/*
* разбивает строки на подстроки по разделителю возвращает массив полстрок
* подстроки могут быть сгруппированы символами группировки тогда
* группа включается в массив как подстрока
*/
void vstr_split(vstr_array_t* arr, vstr_t* str, char* delim, vstr_t* g_open, vstr_t* g_close) {
    long len = str->length, index = 0;
    uint8_t* buf = str->data;
    uint8_t in_group = 0;
    long g_index = -1;
    int is_delim = 0;
    vstr_t* dlms = vstr_dup(delim);

    uint8_t *part = (uint8_t*) malloc(sizeof(uint8_t) * MAX_PART);
        
    for (long i = 0; i < len; i++) {
        
        switch (in_group)  {
            case 0:
                if (vstr_in(dlms, buf[i]) >= 0) {
                    if (!is_delim) {
                        part[index] = '\0';
                        vstr_array_adds(arr, (char*)part);
                        index = 0;
                        is_delim = 1;
                    }
                }
                else {
                    is_delim = 0;
                }

                if(g_open && (g_index = vstr_in(g_open, buf[i])) >= 0) {
                    in_group = 1;
                    is_delim = 1;
                } 
                else if (!is_delim)  {
                    part[index++] = buf[i];
                }
                break;
            case 1:
                if (buf[i] == vstr_at(g_close, g_index)) {
                    part[index] = '\0';
                    vstr_array_adds(arr, (char*)part);
                    index = 0;
                    in_group = 0;
                    g_index = -1;
                }
                else {
                    part[index++] = buf[i];
                }
                break;
            default:
                break;
        }

    }
    if (index > 0) {
        part[index] = '\0';
        vstr_array_adds(arr, (char*)part);    
    }
    vstr_free(dlms);
    free(part);
}



void vstr_put_ch(vstr_t *str, char ch) {
    if(str->length < str->size - 1) {
        str->data[str->length] = (uint8_t) ch;
        str->length++;
        str->data[str->length] = '\0';
    }
}

/*
* декодирует url строку в русские буквы
*/
void vstr_urldecode(vstr_t *str) {
    uint8_t buf[4096];
	uint8_t ch;
	state_t state = ONE;
	long index, buf_index = 0;
    int decode = 0;
    long len = str->length;

    for (long i = 0; i < len; i++) {

		if (str->data[i] == '%') {
            decode = 1;
			continue;
        }
		index = inhex(str->data[i]);
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
			buf[buf_index++] = str->data[i];
		}
	}
	buf[buf_index++] = '\0';
    vstr_assign(str, (char*) buf);
}

/*
* отсекает часть строки с начала или с конца
*/
void vstr_cut(vstr_t* str, long count, int where) {
    long start, end, index = 0;
    uint8_t* tmp = NULL;
    if (count >= str->length)
        return;
    str->size = str->length - count + 1;
    tmp = (uint8_t*)malloc(sizeof(uint8_t) * (str->length - count + 1));
    if (where == 0) {
        start = count;
        end = str->length;    
    }
    else {
        start = 0;
        end = str->length - count;
    }
    for (long i = start; i < end; i++) {
        tmp[index++] = str->data[i];
    }
    tmp[index] = '\0';
    free(str->data);
    str->data = tmp;
    str->length -= count;
}

/*
* заменяет символы в строки на на указанный символ
* если символ 0 то просто удаляет символы из строки
*/
void vstr_replace(vstr_t* str, char* what, char c)
{
    size_t index = 0;
    char* tmp = (char*) malloc(sizeof(char) * str->length);
    vstr_t* w = vstr_dup(what);
    for (long i = 0; i < str->length; i++)
    {
        if (vstr_in(w, str->data[i]) >= 0)
        {
            if (c > 0)
                tmp[index++] = c;
        }
        else
            tmp[index++] = str->data[i];
    }
    tmp[index] = '\0';
    vstr_assign(str, tmp);
}

void vstr_tolower(vstr_t* str)
{
    uint8_t ch;
    long index = 0;

    while (index < str->length)
    {
         ch = str->data[index];
         if (ch < 128)
         {
            ch = tolower(ch);
            str->data[index++] = ch;
         }
         else
         {
            ch = str->data[index+1];
            if (ch >= 0x90 && ch <= 0xaf)
            {
                str->data[index+1] = ch + 0x20;    
            }
            else if (ch == 0x81) {
                str->data[index] = 0xd1;
                str->data[index+1] = 0x91;
            }
            
            
            printf("%x\n", str->data[index+1]);
            //str->data[index+1] += 0x20;
            index += 2;
         }
    }
}

/*
****************************************************************************
* vstr_array functions
*
*****************************************************************************
*/
static int vstr_array_resize(vstr_array_t *arr);

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
    for (long i = 0; i < arr->length; i++)  {
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
    for (long i = 0; i < arr->length; i++) {
        free(arr->array[i]);        
    }
    free(arr->array);
    free(arr);
}

/*
* возвращает длину массива
*/
long vstr_array_length(vstr_array_t* arr)
{
    return arr->length;
}


/*
* очищает массив
*/
void vstr_array_clear(vstr_array_t* arr) {
    for (long i = 0; i < arr->length; i++) {
        free(arr->array[i]);        
    }
    arr->length = 0;
}

/*
* добавляет в массив объект строки vstr_t
*/
long vstr_array_addv(vstr_array_t* arr, vstr_t* str) {
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
long vstr_array_adds(vstr_array_t* arr, const char* str) {
    vstr_t* vstr = vstr_dup(str);
    if(vstr == NULL)
        return -1;

    return vstr_array_addv(arr, vstr);    
}

vstr_t* vstr_array_get(vstr_array_t* arr, long index) {
    if (index >= arr->length)
        return NULL;
    return arr->array[index];    
}
void vstr_array_print(vstr_array_t* arr, FILE* f) {
    for (long i = 0; i < arr->length; i++) {
        vstr_print(arr->array[i], f);
    }
}

vstr_t* vstr_array_join(vstr_array_t* arr, char* delim) {
    long len_delim  = strlen(delim);
    long len_str = 0;
    vstr_t* str = NULL;
    for (long i = 0; i < arr->length; i++) {
        len_str += arr->array[i]->length;
    }
    len_str += (len_delim * (arr->length - 1));
    
    str = vstr_create(len_str);
    len_str = 0;
    for (long i = 0; i < arr->length - 1; i++) {
        memcpy(str->data + len_str, arr->array[i]->data, arr->array[i]->length);
        len_str +=  arr->array[i]->length;
        memcpy(str->data + len_str, delim, len_delim);
        len_str +=  len_delim;
    }
    memcpy(str->data + len_str, arr->array[arr->length - 1]->data, 
            arr->array[arr->length - 1]->length);
    len_str += arr->array[arr->length - 1]->length;
    str->length = len_str;
    str->data[len_str] = '\0';
    return str;
}