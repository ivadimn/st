#ifndef _unp_h
#define _unp_h

#include <sys/types.h>  //основные системные типы данных
#include <sys/socket.h> //основные определения сокетов
#include <netinet/in.h> //структра sockaddr_in{} и другие сетевые определения
#include <arpa/inet.h>  //inet(3) функции
#include <fcntl.h>      //для неблокируемых сокетов
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <sys/stat.h>   //для констант S_xxx
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>     //для доменных сокетов
#include <stdio.h>

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

#ifdef __osf__
#undef recv
#undef send
#define recv(a,b,c,d) recvfrom(a,b,c,d,0,0)
#define send(a,b,c,d) sendto(a,b,c,d.0,0)
#endif

#ifndef INADDR_MODE
#define INADDR_MODE 0xffffffff  //должно быть в <netinet/in.h>
#endif

#ifndef SHUT_RD //три новые константы POSIX.1g
#define SHUT_RD     0
#define SHUT_WR     1
#define SHUT_RDWR   2
#endif

#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN     16  //ddd.ddd.ddd.ddd\e0
#endif

/* Нужно, даже если нет поддержки IPv6, чтобы мы всегда могли
разместить в памяти буфер требуемого размера без директив #ifdef
*/
#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN     46  //максимальная длина строки адреса IPv6
/*
xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx или
xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:ddd.ddd.ddd.ddd\e0
*/ 
#endif

#ifndef HAVE_BZERO
#define bzero(ptr, n)   memset(ptr, 0,  n)
#endif

/* В более старых распознавателях отсутствует gethostbyname2()*/
#ifndef HAVE_GETHOSTBYNAME2
#define gethostbyname2(host, family)    gethostbyname((host))
#endif


/* Нам нужны более новые макросы CMSG_LEN() и CMSG_SPACE(), но в
настоящее время их поддерживают не все реализации. Им требуется 
макрос ALIGN(), но это зависит от реализации
*/
#ifndef CMSG_LEN
#define CMSG_LEN(size)  (sizeof(struct cmsghdr) + (size))
#endif

#ifndef CMSG_SPACE
#define CMSG_SPACE(size)  (sizeof(struct cmsghdr) + (size))
#endif

/* POSIX требует макрос SUN_LEN(), но он определён 
не во всех реализациях. Этот макрос 4.4BSD работает
независимо от того имеется ли поле длины
*/
#ifndef SUN_LEN
#define SUN_LEN(su) \
  (sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif

/* В POSIX "домен UNIX" называется "локальным IPC"
Но пока не во всех системах определены AF_LOCAL и PF_LOCAL
*/
#ifndef AF_LOCAL   
#define AF_LOCAL    AF_UNIX
#endif

#ifndef PF_LOCAL   
#define PF_LOCAL    PF_UNIX
#endif

/* Это значение можно было бы извлеч из SOMAXCONN в <sys/socket.h>
   но многие ядра по прежнему определяют его как 5, хотя на самом деле
   поддерживается гораздо больше 
*/
#define LISTENQ     1024
#define MAXLINE     4096
#define BUFFSIZE    8192

#define SERV_PORT       9877
#define SERV_PORT_STR   "9877"

#define UNIXSTR_PATH    "/tmp/unix.str"
#define UNIXDG_PATH    "/tmp/unix dg"

/* Дальнейшие определения сокращают преобразования типов аргументов-
указателей
*/
#define SA  struct sockaddr

#define HAVE_STRUCT_SOCKADDR_STORAGE
#ifndef HAVE_STRUCT_SOCKADDR_STORAGE
/*
* RFC 3493: протокольно-независимая структура адреса
*/
#define __SS_MAXSIZE    128
#define __SS_ALIGNSIZE  (sizeof(int64_t))
#ifndef HAVE_SOCKADDR_SA_LEN
#define _SS_PADS1SIZE   (_SS_ALIGNSIZE - sizeof(u_char) - sizeof(sa_family_t))
#else
#define _SS_PAD1SIZE   (_SS_ALIGNSIZE - sizeof(sa_family_t))
#endif
#define _SS_PAD2SIZE   (_SS_MAXSIZE - 2*_SS_ALIGNSIZE))
struct sockaddr_storage {
#ifdef HAVE_SOCKADDR_SA_LEN
    u_char ss_len;
#endif
    sa_family_t ss_family;
    char __ss_pad1[__SS_PAD1SIZE];
    int64_t __ss_align;
    char __ss_pad2[__SS_PAD2SIZE];
};

#endif
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef void Sigfunc(int);    // для обработчиков сигналов

#define min(a, b)   ((a) < (b) ? (a) : (b))
#define max(a, b)   ((a) > (b) ? (a) : (b))

#ifndef HAVE_IF_NAMEINDEX_STRUCT
struct if_nameindex {
    unsigned int if_index;
    char *if_name;
};
#endif

/*
* определение функций обёрток
*/

int Socket(int family, int type, int protocol);
void Inet_pton(int family, const char* addrstr, void* buf);
void Connect(int fd, const struct sockaddr* servaddr, socklen_t len);
void Fputs(char* buff, FILE* stream);

#endif