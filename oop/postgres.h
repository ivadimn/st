#ifndef _POSTGRES_H_
#define _POSTGRES_H_

#include <libpq-fe.h>
#include "connection.h"
#include "param.h"
#include "../lib/src/array.h"

void exit_nicely(PGconn *conn);
void show_binary_results(PGresult *res);
PGresult* do_select(conn_t* conn, char *sql, param_list_t* params, size_t pcount);
int do_insert(conn_t* conn, char *sql, array_t* arr, size_t pcount, size_t row_count);

#endif