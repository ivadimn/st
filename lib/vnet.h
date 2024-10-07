#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <liburing.h>

#define ISVALIDSOCKET(s)    ((s) >= 0)
#define CLOSESOCKET(s)      close(s)
#define SOCKET  int
#define bzero(ptr, n)   memset(ptr, 0, n)

#define MAX_CONNECTIONS 4096
#define MAXLINE         4096
#define BUFFSIZE        8192
#define ADDRBUFFSIZE    128


typedef struct conn_info {
    int fd;
    unsigned type;
    int is_working;
    struct sockaddr_storage client_addr;
} conn_info;

enum {
    ACCEPT, READ, WRITE
};



