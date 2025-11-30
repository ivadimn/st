#include "vnet.h"
#include "../lib/src/log.h"

int vsocket(int family, int type, int protocol)
{
    int sckt;
    sckt = socket(family, type, protocol);
    if (!ISVALIDSOCKET(sckt))
    {
        err("Ошибка создания сокета");
        exit(errno);
    }
    return sckt;
}

void vthread_mutex_lock(pthread_mutex_t *mptr)
{
    int n;
    if ((n = pthread_mutex_lock(mptr)) == 0)
        return;
    errno = n;
    err("Ошибка блокировки мьютекса");
}

void vbind(socket_t s, struct sockaddr* addr, socklen_t len)
{
    int n;
    if ((n = bind(s, addr, len)) == 0)
        return
    errno = n;
    err("Ошибка привязки адреса");
}

