#include "../lib/log.h"
#include "../lib/vnet.h"
#include <liburing.h>

conn_info conns[MAX_CONNECTIONS];
char bufs[MAX_CONNECTIONS][MAXLINE];

void add_socket_read(struct io_uring *ring, int fd, size_t size);

void add_socket_write(struct io_uring *ring, int fd, size_t size);


int main(int argc, char **argv)
{
    int conin = fileno(stdin);
    int conout = fileno(stdout);

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s host port", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("Configure remote address...\n");
    struct addrinfo hints;
    bzero(&hints, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *peer_address;
    if (getaddrinfo(argv[1], argv[2], &hints, &peer_address))
        err_sys("getaddrinfo() failed.");
    
    printf("Remote address is: ");
    char address_buffer[128];
    char service_buffer[128];
    getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen, 
                address_buffer, sizeof(address_buffer), 
                service_buffer, sizeof(service_buffer),
                NI_NUMERICHOST);
    printf("%s %s\n", address_buffer, service_buffer);

    printf("Creating socket...");
    SOCKET socket_peer;
    socket_peer = socket(peer_address->ai_family, 
                peer_address->ai_socktype, peer_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_peer))
        err_sys("socket() faild");


    printf("Connecting...\n");
    if (connect(socket_peer, peer_address->ai_addr, peer_address->ai_addrlen))
        err_sys("connect() failed.");
    freeaddrinfo(peer_address);

    printf("Connected\n");

    struct io_uring ring;
    struct io_uring_params params;
    memset(&params, 0, sizeof(params));

    // инициализация io_uring, params передаются пустые и заполняются
    // в случае успешной инициализации
    if(io_uring_queue_init_params(MAX_CONNECTIONS, &ring, &params) < 0)
    {
        err_sys("Error io_uring_queue_init_params: ");
    }


    printf("To send data? enter text followed by enter.\n");
    add_socket_read(&ring, socket_peer, MAXLINE);
    add_socket_read(&ring, conin, MAXLINE);

    struct io_uring_cqe* cqes[MAX_CONNECTIONS];
    while (1)
    {
        // подписываемся на добавленные в sqe события 
        if(io_uring_submit(&ring) < 0)
            err_sys("Error io_uring_submit: ");

        struct io_uring_cqe* cqe;
        // ожидаем наступление событий на котрые мы подписались в sqe
        // выполненные события помещаются в cqe
        if(io_uring_wait_cqe(&ring, &cqe) < 0)
            err_sys("Error io_uring_submit: ");

        // получаем массив состоявшихся событий в количестве count и кладём их в буфер cqes
        int count = io_uring_peek_batch_cqe(&ring, cqes, MAX_CONNECTIONS);    

        for (int i = 0; i < count; i++)
        {
            // значение результата зависит от типа операции
            int result = cqes[i]->res;
            conn_info *ud = (struct conn_info*) cqes[i]->user_data;

            // есть что прочитать
            if (ud->type == READ)
            {
                if (ud->fd == conin)
                {
                    //получили с консоли данные, скопировали их в буфер сокета
                    //и поставили в очередь на отправку
                    printf("Прочитано с консоли %d байт\n", result);
                    strncpy(bufs[socket_peer], bufs[conin], result);
                    add_socket_read(&ring, conin, MAXLINE);
                    add_socket_write(&ring, socket_peer, result);
                }
                else if (ud->fd == socket_peer)
                {
                    if (result <= 0)
                    // если прочитали 0 то закрываем соединение
                        shutdown(ud->fd, SHUT_RDWR);
                    else {
                    //получили с сервера данные, скопировали их в буфер консоли вывода
                    //и поставили в очередь на печать
                        strncpy(bufs[conout], bufs[socket_peer], result);
                        add_socket_write(&ring, conout, result);        
                        add_socket_read(&ring, socket_peer, MAXLINE);
                    }    
                }
            }
            else if (ud->type == WRITE)
            {
                if (ud->fd == socket_peer)
                {
                    printf("В сокет записали %d байт\n", result);
                    add_socket_read(&ring, socket_peer, MAXLINE);
                }
                
            }
                
            io_uring_cqe_seen(&ring, cqes[i]);
        }    
    }
}

void add_socket_read(struct io_uring *ring, int fd, size_t size)
{
    // получить экземпляр очереди sqe для заполнения
    struct io_uring_sqe *sqe = io_uring_get_sqe(ring);
    //готовим fd к чтению 
    // читать будем в bufs - предаллоцированный массиы буферов по количеству соединений
    io_uring_prep_read(sqe, fd, bufs[fd], size, 0);
    // записываем общую для sqe и cqe область данных информацию сокете из которого будем читать
    conn_info *conn = &conns[fd];
    conn->fd = fd;
    conn->type = READ;
    io_uring_sqe_set_data(sqe, conn);
}

void add_socket_write(struct io_uring *ring, int fd, size_t size)
{
    // получить экземпляр очереди sqe для заполнения
    struct io_uring_sqe *sqe = io_uring_get_sqe(ring);
    //готовим fd к записи 
    // писать будем из bufs в котрый раньше читали
    io_uring_prep_write(sqe, fd, bufs[fd], size, 0);
    // записываем общую для sqe и cqe область данных информацию сокете в котрый будем писать
    conn_info *conn = &conns[fd];
    conn->fd = fd;
    conn->type = WRITE;
    io_uring_sqe_set_data(sqe, conn);
}

