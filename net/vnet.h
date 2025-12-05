#ifndef _VNET_H_
#define _VNET_H_

#include <sys/types.h>      //основные системные типы данных
#include <sys/socket.h>     //основные определния сокетов
#include <netinet/in.h>     //структура sockaddr_in и другие сетевые определения
#include <sys/time.h>       //структура timeval для функции select
#include <time.h>           //структура timespec для функции pselect
#include <arpa/inet.h>      //inet функции
#include <sys/stat.h>       //для констант S_xxx
#include <sys/uio.h>        //для структуры iovec и readv/writev
#include <sys/wait.h>
#include <sys/un.h>         //для доменных сокетов
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>          //для неблокируемых сокетов
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define ISVALIDSOCKET(s)    ((s) >= 0)
#define CLOSESOCKET(s)      close(s)
#define GETSOCKETERRNO()    (errno)
#define bzero(ptr,n)        memset(ptr,0, n)
#define MAXLINE             4096
#define BUFFSIZE            8192

#define BACKLOG             32
//#define SA                  struct sockaddr 
typedef struct sockaddr     SA;
typedef int                 socket_t;
typedef struct addrinfo     AI;


/*
* функции обёртки
*/

int vsocket(int family, int type, int protocol);
void vthread_mutex_lock(pthread_mutex_t *mptr);
void vgetaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);

void vbind(socket_t s, struct sockaddr *addr, socklen_t len);
void vlisten(socket_t s, int backlog);
socket_t vaccept(socket_t s, struct sockaddr *addr, socklen_t len);

socket_t init_server_default(const char* service);

#endif