#ifndef _VNET_H_
#define _VNET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define ISVALIDSOCKET(s)    ((s) >= 0)
#define CLOSESOCKET(s)      close(s)
#define GETSOCKETERRNO()    (errno)

#endif