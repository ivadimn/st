#include <stdlib.h>
#include <sqlite3.h>

#include "db.h"
#include "log.h"

#define SQL_LEN 4096
#define ERR_MSG_LEN 256
#define NAME_LEN 64
#define INFO_LEN 32
#define IP4_LEN 16


#define INVALID_PARAM -1

typedef struct conn_t {
    sqlite3 *db;
    char dbname[INFO_LEN];
} conn_t;


static char sql[SQL_LEN];
static char error_message[ERR_MSG_LEN];

sqlite3* get_db(conn_t* conn)
{
    return conn->db;
}


conn_t* create_conn(const char* db_name)
{
    conn_t* conn = (conn_t*)malloc(sizeof(conn_t));
    if (conn == NULL)
        crit("Ошибка выделения памяти\n");
    strncpy(conn->dbname, db_name, INFO_LEN - 1);
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


long selectv(conn_t* conn, const char* command, 
            result_list_t func, void* data, param_list_t* params)
{
    long result;
    sqlite3_stmt* stmt; 

    if(sqlite3_prepare_v2(conn->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Ошибка подготовки SQL-запроса: %s\n", sqlite3_errmsg(conn->db));
        sqlite3_finalize(stmt);
        return -1;
    }

    
    result = func(stmt, data, params);
        
    if(result != SQLITE_DONE) {
        printf("Ошибка выполнения SQL-запроса: %s\n", sqlite3_errmsg(conn->db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    return 0;        
}

