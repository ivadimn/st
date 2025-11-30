#include <time.h>
#include "vnet.h"

int main(int argc, char** argv)
{
    socket_t listenfd, connfd;
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    time_t ticks;

    //сокет слушающий и принимающий соединения
    listenfd = vsocket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));

}