#ifndef _POSTGRES_H_
#define _POSTGRES_H_

#include <libpq-fe.h>

void exit_nicely(PGconn *conn);
void show_binary_results(PGresult *res);


#endif