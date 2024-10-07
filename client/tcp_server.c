#include "../lib/vnet.h"
#include "../lib/log.h"
#include <ctype.h>


conn_info conns[MAX_CONNECTIONS];
char bufs[MAX_CONNECTIONS][MAXLINE];

void add_accept(struct io_uring *ring, int fd, struct sockaddr* client_addr, socklen_t* client_len);

void add_socket_read(struct io_uring *ring, int fd, size_t size);

void add_socket_write(struct io_uring *ring, int fd, size_t size);



int main(int argc, char** argv)
{
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    if (argc != 2)
    {
        fprintf(stderr, "Usage %s port.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    SOCKET serv_socket;

    //формируем адрес сервера для прослушивания
    struct addrinfo hints, *serv_address;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(0, argv[1], &hints, &serv_address);

    char address_buffer[128];
    getnameinfo((struct sockaddr*) serv_address, sizeof(struct sockaddr_in), 
            address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);

    printf("Creating socket on address %s\n", address_buffer);

    serv_socket = socket(serv_address->ai_family, serv_address->ai_socktype, 
                        serv_address->ai_protocol);
    if (!ISVALIDSOCKET(serv_socket))
        err_sys("Error while creating socket ");

    printf("Binding socket to address %s\n", address_buffer);
    if (bind(serv_socket, serv_address->ai_addr, serv_address->ai_addrlen))
        err_sys("Error while binding socket ");
    
    freeaddrinfo(serv_address);

    printf("Listening...\n");
    if (listen(serv_socket, MAX_CONNECTIONS) < 0)
        err_sys("Error while begin listening ");

    struct io_uring ring;
    struct io_uring_params params;
    
    memset(&params, 0, sizeof(params));    

    //здесь мы создаём непосредственно io_uring, с пустыми параметрами
    if(io_uring_queue_init_params(MAX_CONNECTIONS, &ring, &params) < 0)
        err_sys("Error while creating io_uring ");

    add_accept(&ring, serv_socket, (struct sockaddr*) &client_address, &client_len);
    while (1)
    {
        //подписываемся на ранее добавленные в ring события
        if (io_uring_submit(&ring) < 0)
            err_sys("Error while submiting ");

        struct io_uring_cqe* cqe;
        //здесь мы ожидаем наступление событий на которые мы подписались
        //результаты наступления событий помещаются в cqe
        if (io_uring_wait_cqe(&ring, &cqe) < 0)
            err_sys("Error while waiting cqes ");

        struct io_uring_cqe* cqes[MAX_CONNECTIONS];
        int count = io_uring_peek_batch_cqe(&ring, cqes, MAX_CONNECTIONS);

        //обрабатываем полученные события
        for (int i = 0; i < count; i++)
        {
            int result = cqes[i]->res;      //result - контекстно-зависим от типа события
            conn_info *ud = (struct conn_info*) cqes[i]->user_data;

            if (ud->type == ACCEPT)
            {
                memcpy(&ud->client_addr, &client_address, client_len);
                add_socket_read(&ring, result, MAXLINE);
                char address_buffer[ADDRBUFFSIZE];
                getnameinfo((struct sockaddr*) &ud->client_addr, client_len, 
                            address_buffer, ADDRBUFFSIZE, 0, 0, NI_NUMERICHOST);
                printf("Подключились с адреса %s\n", address_buffer);

                add_accept(&ring, serv_socket, (struct sockaddr*) &client_address, &client_len);
            }
            else if (ud->type == READ)
            {
                if (result <= 0)
                {
                    shutdown(ud->fd, SHUT_RDWR);
                    printf("закрыли соединение\n");
                }
                else
                {
                    for (int i = 0; i < result; i++)
                    {
                        bufs[ud->fd][i] = toupper(bufs[ud->fd][i]);
                    }
                    add_socket_write(&ring, ud->fd, result);
                    for (int i = 0; i < MAX_CONNECTIONS; i++)
                    {
                        if (conns[i].is_working == 1)
                        {
                            printf("Сокет в работе %d\n", conns[i].fd);
                        }
                        if (conns[i].fd == ud->fd || conns[i].fd == serv_socket)
                            continue;
                        else 
                        {
                            if (conns[i].is_working == 1)
                            {
                                strncpy(bufs[conns[i].fd], bufs[ud->fd], result);
                                add_socket_write(&ring, conns[i].fd, result);
                                printf("Добавили в запись соседа %d\n", conns[i].fd);
                            }
                        }
                    }
                }
            }
            else if (ud->type == WRITE)
            {
                add_socket_read(&ring, ud->fd, MAXLINE);
                printf("Записали %s и добавили снова в чтение\n", bufs[ud->fd]);
            }
            io_uring_cqe_seen(&ring, cqes[i]);
        }
    }
    exit(EXIT_SUCCESS);
}


void add_accept(struct io_uring *ring, int fd, struct sockaddr* client_addr, 
                socklen_t* client_len)
{
    // получить экземпляр очереди sqe для заполнения
    struct io_uring_sqe *sqe = io_uring_get_sqe(ring);
    //готовим fd к приёму соединений 
    //в client_addr положится адрес клиента
    io_uring_prep_accept(sqe, fd, client_addr, client_len, 0);
    // записываем общую для sqe и cqe область данных информацию о серверном сокете и его состоянии
    conn_info *conn = &conns[fd];
    conn->fd = fd;
    conn->type = ACCEPT;
    conn->is_working = 1;

    io_uring_sqe_set_data(sqe, conn);
}

void add_socket_read(struct io_uring *ring, int fd, size_t size)
{
    // получить экземпляр очереди sqe для заполнения
    struct io_uring_sqe *sqe = io_uring_get_sqe(ring);
    //готовим fd к чтению данных из сети в буфер
    io_uring_prep_read(sqe, fd, bufs[fd], size, 0);
    // записываем общую для sqe и cqe область данных информацию о серверном сокете и его состоянии
    conn_info *conn = &conns[fd];
    conn->fd = fd;
    conn->type = READ;

    io_uring_sqe_set_data(sqe, conn);

}

void add_socket_write(struct io_uring *ring, int fd, size_t size)
{
    // получить экземпляр очереди sqe для заполнения
    struct io_uring_sqe *sqe = io_uring_get_sqe(ring);
    //готовим fd к чтению данных из сети в буфер
    io_uring_prep_write(sqe, fd, bufs[fd], size, 0);
    // записываем общую для sqe и cqe область данных информацию о серверном сокете и его состоянии
    conn_info *conn = &conns[fd];
    conn->fd = fd;
    conn->type = WRITE;

    io_uring_sqe_set_data(sqe, conn);
}