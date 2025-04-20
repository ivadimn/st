#include "db.h"
#include "../log.h"

static char sql[SQL_LEN];
static char error_message[ERR_MSG_LEN];

static char *sql_stat = "SELECT %s(%s) FROM %s; ";
static char *sql_disp = "SELECT AVG((%s - %f) * (%s - %f)) FROM %s; ";

sqlite3* open_db(char *dbname)
{
    sqlite3 *db;
    if (sqlite3_open(dbname, &db) != SQLITE_OK)
    {
        sqlite3_close(db);
        err_sys("Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
    }
    return db;
}

void close_db(sqlite3* db)
{
    sqlite3_close(db);
}

char *get_err_msg()
{
    return error_message;
}

