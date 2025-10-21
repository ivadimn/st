#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <libpq-fe.h>

#define PARAM_LEN 32
#define CONN_STR_LEN 256
#define ERR_MSG_LEN 1024

typedef struct conn_param_t
{
    char host[PARAM_LEN];
    char port[PARAM_LEN];
    char user[PARAM_LEN];
    char pwd[PARAM_LEN];
    char dbname[PARAM_LEN];
} conn_param_t;


typedef struct conn_t
{
    PGconn* db;
    char conn_str[CONN_STR_LEN];
    char error_message[ERR_MSG_LEN];
} conn_t;

conn_param_t* init_conn_param(const char* host,
                            const char* port,
                            const char* user,
                            const char* pwd,
                            const char* dbname);

void release_conn_param(conn_param_t* cp);

conn_t* new_connection(conn_param_t *cp);
void del_connection(conn_t* conn);

void connect1(conn_t *conn);
void disconnect(conn_t* conn);


#endif