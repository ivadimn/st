#include "vnet.h"
#include <time.h>

int main(int argc, char** argv)
{
    //стандартные процедуры конфигурирования серверного сокета
    printf("Confuguring local address...\n");
    struct addrinfo hints, *bind_address;
    
    //конфигурируем локальные для привязки к порту
    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;          //IPv4
    hints.ai_socktype = SOCK_STREAM;    //TCP protocol
    hints.ai_flags = AI_PASSIVE;        //любой доступный сетевой интерфейс

    /*
    * используем getaddrinfo для заполнения структуры addrinfo (bind_address)
    */
    vgetaddrinfo(0, "8080", &hints, &bind_address);

    printf("Creating socket...\n");
    socket_t serv_socket;
    serv_socket = vsocket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);

    printf("Binding socket to local address...\n");
    vbind(serv_socket, bind_address->ai_addr, bind_address->ai_addrlen);
    
    freeaddrinfo(bind_address);

    printf("Listening...\n");
    vlisten(serv_socket, BACKLOG);

    printf("Waiting for connection...\n");
    // дальше надо всё обернуть в цикл
    struct sockaddr_storage client_address;     //для сохранения адреса соединённого клиента
    socklen_t client_len = sizeof(client_address);
    socket_t client_socket = vaccept(serv_socket, (SA*) &client_address, client_len);
    if (client_socket < 0)
        exit(1);
    printf("Client connected...\n");
    
    char address_buffer[100];
    getnameinfo((SA*) &client_address, client_len, address_buffer, 
                 sizeof(address_buffer), 0 /*имя сервиса*/, 0, NI_NUMERICHOST);
    
    printf("%s\n", address_buffer);

    printf("Reading request...\n");
    char request[BUFFSIZE];
    int bytes_reсevid = recv(client_socket, request, BUFFSIZE, 0);
    printf("Получили %d байт\n", bytes_reсevid);
    printf("%.*s\n", bytes_reсevid, request);
    printf("Sending response...\n");

    // отправляем стандартный заголовок ответа и начало нашего сообщения
    const char *response = 
        "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Local time is: ";                  //начало сообщения
    int bytes_sent = send(client_socket, response, strlen(response), 0);
    printf("Отправлено %d байт из %d байт\n", bytes_sent, (int) strlen(response));    

    time_t timer;
    time(&timer);
    char *time_msg = ctime(&timer);
    bytes_sent = send(client_socket, time_msg, strlen(time_msg), 0);
    printf("Отправлено %d байт из %d байт\n", bytes_sent, (int) strlen(time_msg));
    
    printf("Closing connection...\n");
    CLOSESOCKET(client_socket);

    printf("Closing listening socket...\n");
    CLOSESOCKET(serv_socket);

    printf("Finished.\n");
    return 0;

}