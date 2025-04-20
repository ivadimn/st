#ifndef _UTILS_H_
#define _UTILS_H_

#include <stddef.h>
#include "vstr.h"

#define MAX_PATH        1024
#define MAX_PART        8192
#define DEFAULT_SIZE    4096
#define LINE_SIZE       8192
#define MAX_FILE_SIZE   8388608

char** init_file_list(size_t count);
void free_file_list(char** flist, size_t count);

vstr_array_t* get_strings_from_file(const char* filename);


size_t get_file_size(int fd);
int is_dir(const char* file);

void file_list(char *dir, char** flist);
size_t get_count_files(char *dir);
void* alloc(size_t size);

#endif