#include <ifaddrs.h>
#include "vnet.h"
#include "../lib/src/log.h"


int time_client(char* host)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    sockfd = vsocket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    if (inet_pton(AF_INET, host, &servaddr.sin_addr) <= 0)
    {
        crit("Ошибка трансляции адреса %s", host);
    }

    if (connect(sockfd,(SA *) &servaddr, sizeof(servaddr)) < 0)
    {
        crit("Ошибка соединения: ");
    }
    while ((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
    if (n < 0)
    {
        err("Ошибка чтения сокета: ");
    }
    return 0;
}

int adapters_list()
{
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];
    

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    /* Iterate through the linked list of interface addresses */
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        printf("Interface: %s\n", ifa->ifa_name);
        printf("  Flags: 0x%x\n", ifa->ifa_flags);

        /* Display interface address and netmask */
        if (family == AF_INET || family == AF_INET6) {
            s = getnameinfo(ifa->ifa_addr,
                            (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                                  sizeof(struct sockaddr_in6),
                            host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0) {
                printf("  getnameinfo() failed: %s\n", gai_strerror(s));
                continue;
            }
            printf("  Address: %s\n", host);

            if (ifa->ifa_netmask != NULL) {
                s = getnameinfo(ifa->ifa_netmask,
                                (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                                      sizeof(struct sockaddr_in6),
                                host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
                if (s != 0) {
                    printf("  getnameinfo() failed for netmask: %s\n", gai_strerror(s));
                } else {
                    printf("  Netmask: %s\n", host);
                }
            }

            /* Display broadcast or destination address for point-to-point links */
            if (/*ifa->ifa_flags & IFF_BROADCAST &&*/ ifa->ifa_broadaddr != NULL) {
                s = getnameinfo(ifa->ifa_broadaddr,
                                (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                                      sizeof(struct sockaddr_in6),
                                host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
                if (s != 0) {
                    printf("  getnameinfo() failed for broadcast address: %s\n", gai_strerror(s));
                } else {
                    printf("  Broadcast Address: %s\n", host);
                }
            } else if (/*ifa->ifa_flags & IFF_POINTOPOINT &&*/ ifa->ifa_dstaddr != NULL) {
                s = getnameinfo(ifa->ifa_dstaddr,
                                (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                                      sizeof(struct sockaddr_in6),
                                host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
                if (s != 0) {
                    printf("  getnameinfo() failed for destination address: %s\n", gai_strerror(s));
                } else {
                    printf("  Destination Address: %s\n", host);
                }
            }
        }
        printf("\n");
    }

    freeifaddrs(ifaddr); /* Free the memory allocated by getifaddrs */
    return 0;
}

void ltime()
{
    time_t timer;
    time(&timer);
    printf("Local time is %s\n", ctime(&timer)); 
}


int main(int argc, char** argv)
{
    //adapters_list();
    //ltime();
    if (argc != 2)
    {
        info("info Использование ./main ipaddress");
        //debug("debug Использование ./main ipaddress");
        //warning("warning Использование ./main ipaddress");
        //err("err Использование ./main ipaddress");
        crit("crit Использование ./main ipaddress");
        return 1;
    }
    time_client(argv[1]);
    return 0;
}