#include <stdio.h>
#include <stdlib.h>
#include "connection.h"
#include "../lib/src/log.h"

conn_param_t* init_conn_param(const char* host,
                            const char* port,
                            const char* user,
                            const char* pwd,
                            const char* dbname)
{
    conn_param_t* cp = (conn_param_t*) malloc(sizeof(conn_param_t));
    if (cp == NULL)
        crit("Ошибка распределения памяти при создании параметров соединения с БД.");
    
    strncpy(cp->host, host, PARAM_LEN - 1);
    strncpy(cp->port, port, PARAM_LEN - 1);
    strncpy(cp->user, user, PARAM_LEN - 1);
    strncpy(cp->pwd, pwd, PARAM_LEN - 1);
    strncpy(cp->dbname, dbname, PARAM_LEN - 1);
    
    return cp;
}

void release_conn_param(conn_param_t* cp)
{
    free(cp);
}

conn_t* new_connection(conn_param_t *cp)
{
    conn_t* conn = (conn_t*) malloc(sizeof(conn_t));

    if (conn == NULL)
        crit("Ошибка распределения памяти при создании соединения с БД.");
    
    snprintf(conn->conn_str, CONN_STR_LEN - 1, "hostaddr=%s port=%s user=%s password=%s dbname=%s",
            cp->host, cp->port, cp->user, cp->pwd, cp->dbname);
    conn->db = NULL;

    return conn;
}

void del_connection(conn_t* conn)
{
    free(conn);
}

void connect1(conn_t *conn)
{
   
    printf("before call connect %s\n", conn->conn_str);
        
    conn->db = PQconnectdb(conn->conn_str);
    printf("call connect\n");
    if (PQstatus(conn->db) != CONNECTION_OK) {
        printf("connect failure\n");
        err("Ошибка подключения к серверу: %s", PQerrorMessage(conn->db));
        PQfinish(conn->db);
        exit(EXIT_FAILURE);
    }
}

void disconnect(conn_t* conn)
{
    PQfinish(conn->db);
}
