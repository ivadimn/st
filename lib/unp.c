#include "unp.h"
#include "log.h"

int Socket(int family, int type, int protocol)
{
    int fd;
    if ((fd = socket(family, type, protocol)) < 0)
        err_sys("socket error");
    return fd;
}

void Inet_pton(int family, const char* addrstr, void* buf)
{
    if (inet_pton(family, addrstr, buf) <= 0)
        err_quit("inet_pton error for %s", addrstr);
}

void Connect(int fd, const struct sockaddr* servaddr, socklen_t len)
{
    if (connect(fd, servaddr, len) < 0)
        err_sys("connect error");
}

void Fputs(char* buff, FILE* stream)
{
    if (fputs(buff, stream) == EOF)
        err_sys("fputs error");   
}