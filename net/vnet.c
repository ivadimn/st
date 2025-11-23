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

