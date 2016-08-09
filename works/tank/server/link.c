/*
 * link.c
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "logger.h"

static int server_socket = -1;

int link_open(const char *port)
{
	struct sockaddr_in server_addr;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(port));

	socklen_t len = sizeof(struct sockaddr_in);

	if (bind(server_socket, (struct sockaddr *)&server_addr, len) != 0) {
		logger_error("link_open: %s\n", strerror(errno));
		return 0;
	}
	if (listen(server_socket, 5) != 0) {
		logger_error("link_open: %s\n", strerror(errno));
		return 0;
	}
	return 1;
}

void link_close(void)
{
	close(server_socket);
	server_socket = -1;
}

int link_accept(void)
{
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(struct sockaddr_in);
	int client_socket;

	client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &len);
	if (client_socket == -1) {
		logger_error("link_accept: %s\n", strerror(errno));
		return 0;
	}
	return client_socket;
}
