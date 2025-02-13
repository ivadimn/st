#include "log.h"
#include "file_info.h"
#include "utils.h"
#include "vstr.h"

#include <sys/mman.h>

static void get_lines(char* buf);
static void save_data(vstr_array_t* arr); 

void handle_file(char* filename) {

    int fd;
    size_t fsize;
    char *fbuff = NULL;
    

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        err("Ошибка открытия файла: %s", filename);
        return;
    }
    printf("файл открыт\n");

    fsize = get_file_size(fd);
    if (fsize == 0) {
        crit("Ошибка при определении размера файла: %s", filename);
    }
    printf("размер файла %ld\n", fsize);

    fbuff = (char*) mmap(NULL, fsize, PROT_READ, MAP_PRIVATE, fd, 0);

    if (fbuff == NULL) {
        crit("Ошибка распределения памяти");
    }
    
    printf("файл прочитан\n");
    get_lines(fbuff);
    printf("get_lines отработала\n");

    munmap(fbuff, fsize);
    close(fd);
    
}

static void save_data(vstr_array_t* arr)  {

    vstr_array_print(arr, stdout);
    printf("\n");
}


static void get_lines(char* buf) {

    vstr_t *str = vstr_create(LINE_SIZE);
    vstr_t *g_open = vstr_dup("\"["); 
    vstr_t *g_close = vstr_dup("\"]"); 
    vstr_array_t* arr = vstr_array_create(COUNT);
    size_t index = 0;

    char* line = (char*) malloc(sizeof(char*) * LINE_SIZE);

    while (*buf != '\0') {
        if (*buf == '\n')  {
            line[index] = '\0';
            index = 0;
            vstr_assign(str, line);
            vstr_split(arr, str, " ", g_open, g_close);
            save_data(arr);
            vstr_array_clear(arr);
        }
        else {
            line[index++] = *buf;
        }
        buf++;
    }
    free(line);
    vstr_free(str);
    vstr_array_free(arr);
    vstr_free(g_open);
    vstr_free(g_close);
    printf("get_lines отработала in\n");
    return;
}

void get_hosts(char*** hosts, long** bytes) {
    
}

void remove_hosts(char*** hosts, long** bytes) {
    
}