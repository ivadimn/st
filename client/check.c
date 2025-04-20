#include "../lib/vnet.h"
#include <stdlib.h>
#include <liburing.h>


typedef struct conn_info {
    int fd;
    unsigned type;
} conn_info;

enum {
    ACCEPT, READ, WRITE
};

conn_info conns[MAX_CONNECTIONS];
char bufs[MAX_CONNECTIONS][MAXLINE];

void add_socket_read(struct io_uring *ring, int fd, size_t size);

void add_socket_write(struct io_uring *ring, int fd, size_t size);

 int main() {

    int conin = fileno(stdin);
    struct io_uring ring;
    struct io_uring_params params;
    memset(&params, 0, sizeof(params));

    // инициализация io_uring, params передаются пустые и заполняются
    // в случае успешной инициализации
    if(io_uring_queue_init_params(MAX_CONNECTIONS, &ring, &params) < 0)
    {
        printf("Error io_uring_queue_init_params: \n");
        exit(1);
    }

    printf("To send data? enter text followed by enter.\n");
    
    add_socket_read(&ring, conin, MAXLINE);

    struct io_uring_cqe* cqes[MAX_CONNECTIONS];

    while (1)
    {
        // подписываемся на добавленные в sqe события 
        if(io_uring_submit(&ring) < 0) 
        {
            printf("Error io_uring_submit: \n");
            exit(1);
        }
            

        struct io_uring_cqe* cqe;
        // ожидаем наступление событий на котрые мы подписались в sqe
        // выполненные события помещаются в cqe
        if(io_uring_wait_cqe(&ring, &cqe) < 0)
        {
            printf("Error io_uring_wait_cqe: \n");
            exit(1);
        }

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
                printf("%.*s", result, bufs[ud->fd]);
                add_socket_read(&ring, conin, MAXLINE);
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
