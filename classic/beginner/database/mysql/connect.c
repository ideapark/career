/*
 * gcc -Wall connect.c -lmysqlclient
 */

#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>

#include "require-macro.h"

int main(int argc, char *argv[])
{
    MYSQL *conn_ptr;

    conn_ptr = mysql_init(NULL);
    if (!conn_ptr) {
        fprintf(stderr, "mysql_init failed\n");
        return EXIT_FAILURE;
    }

    conn_ptr = mysql_real_connect(conn_ptr, DECLARE_STRING(HOST),
                                  DECLARE_STRING(USER),
                                  DECLARE_STRING(PASSWORD),
                                  DECLARE_STRING(SCHEMA),
                                  0, NULL, 0);

    if (conn_ptr) {
        printf("Connection success\n");
    } else {
        printf("Connection failed\n");
    }

    mysql_close(conn_ptr);

    return 0;
}
