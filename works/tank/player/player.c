/*
 * player.c
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "player.h"
#include "logger.h"
#include "link.h"

/*
 * client command line arguments
 */
static const char *server_ip = "127.0.0.1";
static const char *server_port = "6000";
static const char *client_log = "cli.log";

static struct option client_options[] = {
	{"ip",     required_argument, 0, 'i'},
	{"port",   required_argument, 0, 'p'},
	{"stdout", required_argument, 0, 's'},
	{0,        0,                 0,   0}
};

static int sockfd = -1;

int main(int argc, char *argv[])
{
	int c;
	while ((c = getopt_long(argc, argv, "i:p:s", client_options, NULL)) != -1) {
		switch (c) {
		case 'i':
			server_ip = optarg;
			break;
		case 'p':
			server_port = optarg;
			break;
		case 's':
			client_log = "/dev/stdout";
			break;
		default:
			exit(-1);
		}
	}

	/* logger setup */
	if (!logger_open(client_log))
		exit(-2);

	/* connect server */
	if ((sockfd = link_connect(server_ip, server_port)) == -1)
		exit(-3);

	return 0;
}
