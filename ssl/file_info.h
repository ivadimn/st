#ifndef _FILE_INFO_H_
#define _FILE_INFO_H_

#include <stddef.h>

#define LINE_SIZE 8192

typedef enum {HOST, ID, USER, DATE, REQUEST, 
            STATUS, BYTES, REFERER, AGENT, COUNT} comb_t;


void handle_file(char* filename);
void get_hosts(char*** hosts, long** bytes);
void remove_hosts(char*** hosts, long** bytes);


#endif