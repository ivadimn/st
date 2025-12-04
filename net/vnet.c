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

void vgetaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res)
{
    int result = getaddrinfo(node, service, hints, res);
    if (result != 0)
    {
        err(gai_strerror(result));
        exit(result);
    }
    return;
}

void vbind(socket_t s, struct sockaddr* addr, socklen_t len)
{
    int result = bind(s, addr, len);
    if ( result == 0)
        return;
    err("Ошибка привязки сокета");
    return;
}

void vlisten(socket_t s, int backlog)
{
    int result = listen(s, backlog);
    if (result == 0)
        return;
    err("Ошибка функции listen");
    exit(result);    
}

socket_t vaccept(socket_t s, struct sockaddr *addr, socklen_t len)
{
    socket_t client_socket;
    client_socket = accept(s, addr, &len);
    if (!ISVALIDSOCKET(client_socket))
    {
        err("Ошибка внешнего соединения");
        return - 1;
    }
    return client_socket;
}
