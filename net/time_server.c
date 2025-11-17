#include "vnet.h"



int main(int argc, char** argv)
{
    //стандартные процедуры конфигурирования серверного сокета
    printf("Confuguring local address...\n");
    struct addrinfo hints, *bind_address;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;          //IPv4
    hints.ai_socktype = SOCK_STREAM;    //TCP protocol
    hints.ai_flags = AI_PASSIVE;        //любой доступный сетевой интерфейс

    /*
    * используем getaddrinfo для заполнения структуры addrinfo (bind_address)
    */
    getaddrinfo(0, "8080", &hints, &bind_address);



    freeaddrinfo(bind_address);
    return 0;

}