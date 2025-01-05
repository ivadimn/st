#ifndef _DB_H_
#define _DB_H_

#include <sqlite3.h>

#define SQL_LEN 4096
#define ERR_MSG_LEN 256

sqlite3* open_db(char* conninfo);
void close_db(sqlite3* db);
char* get_err_msg();

#endif