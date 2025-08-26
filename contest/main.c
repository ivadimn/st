#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

char buf[512];
char sql[1024];

static PGconn* db; 

void open_psql(const char* host,
               const char* dbname,
               const char* user,
               const char* pwd) {

    char conninfo[1024];
    sprintf(conninfo, "hostaddr=%s port=5432 user=%s password=%s dbname=%s", 
                host, user, pwd, dbname);
    db = PQconnectdb(conninfo);
    if (PQstatus(db) != CONNECTION_OK) {
        printf("Ошибка подключения к серверу: %s", PQerrorMessage(db));
        PQfinish(db);
        exit(EXIT_FAILURE);
    }
}



int main(int argc, char** argv)
{
    open_psql("10.0.0.101", "gaz", "dev", "7922448");
    printf("Подключились!!\n");
    PQfinish(db);


    return 0;
}