/*
 * link.c
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "link.h"
#include "logger.h"

int link_connect(const char *server_ip, const char *server_port)
{
	int sockfd;
	struct sockaddr_in name;
	struct hostent *hostinfo;

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	name.sin_family = AF_INET;
	hostinfo = gethostbyname(server_ip);
	if (hostinfo == NULL) {
		logger_error("%s\n", "query server ip failed, quit now!");
		return -1;
	} else {
		name.sin_addr = *((struct in_addr *)hostinfo->h_addr);
		name.sin_port = htons(atoi(server_port));
	}
	if (connect(sockfd, (const struct sockaddr *)&name, sizeof(struct sockaddr_in)) == -1) {
		logger_error("%s: %s\n", "connect to server", strerror(errno));
		return -1;
	}
	return sockfd;
}
