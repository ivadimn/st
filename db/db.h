#ifndef _DB_H_
#define _DB_H_

#include <sqlite3.h>

typedef struct conn_t conn_t;

conn_t* create_conn(const char* db_name);
void free_conn(conn_t* conn);
void open_db(conn_t* conn);
void close_db(conn_t* conn);
char* get_err_msg();

sqlite3* get_db(conn_t* conn);

#endif