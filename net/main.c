
#include <stdio.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <time.h>
#include "vnet.h"

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
    ltime();
    return 0;
}