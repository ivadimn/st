#ifndef _DB_H_
#define _DB_H_

#include <sqlite3.h>
#include "param.h"

typedef struct conn_t conn_t;
typedef int (*result_list_t) (sqlite3_stmt *stmt, void* data, param_list_t* params);

conn_t* create_conn(const char* db_name);
void free_conn(conn_t* conn);
void open_db(conn_t* conn);
void close_db(conn_t* conn);
char* get_err_msg();

long select(conn_t* conn, const char* command, result_list_t func, void* data, param_list_t* params);

sqlite3* get_db(conn_t* conn);

#endif