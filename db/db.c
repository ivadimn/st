#include <stdlib.h>
#include <sqlite3.h>

#include "log.h"

#define SQL_LEN 4096
#define ERR_MSG_LEN 256
#define NAME_LEN 64
#define INFO_LEN 32
#define IP4_LEN 16


#define INVALID_PARAM -1

typedef struct {
    sqlite3 *db;
    char dbname[INFO_LEN];
} conn_t;


static char sql[SQL_LEN];
static char error_message[ERR_MSG_LEN];


conn_t* create_conn(const char* db_name)
{
    conn_t* conn = (conn_t*)malloc(sizeof(conn_t));
    if (conn == NULL)
        crit("Ошибка выделения памяти\n");

    return conn;    
}

void free_conn(conn_t* conn)
{
    free(conn);
}

void open_db(conn_t *conn) 
{
    if (sqlite3_open(conn->dbname, &(conn->db)) != SQLITE_OK) 
    {
        strncpy(error_message, sqlite3_errmsg(conn->db), ERR_MSG_LEN - 1);
        crit("Ошибка открытия БД: %s\n", error_message);
    }
}

void close_db(conn_t *conn)
{
    sqlite3_close(conn->db);
}

char* get_err_msg() {
    return error_message;
}


