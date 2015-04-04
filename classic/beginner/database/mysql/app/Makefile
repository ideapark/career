all: app

app: app_mysql.c app_test.c app_mysql.h ../require-macro.h
	gcc -Wall -Wpointer-arith -DHOST=host -DUSER=user -DPASSWORD=password -DSCHEMA=schema app_mysql.c app_test.c -lmysqlclient
