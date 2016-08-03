/*
 * Tank War Server
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <getopt.h>

#include "server.h"
#include "logger.h"
#include "map.h"

/*
 * server command line arguments
 */
static const char *server_port    = "6000";
static const char *server_ip      = "127.0.0.1";
static const char *server_map     = "map.txt";
static const char *server_timeout = "400";
static const char *server_log     = "server.log";

static struct option server_options[] = {
	{"ip",      required_argument, 0, 'i'},
	{"port",    required_argument, 0, 'p'},
	{"map",     required_argument, 0, 'm'},
	{"timeout", required_argument, 0, 't'},
	{"stdout",  no_argument,       0, 's'},
	{0,         0,                 0,   0}
};

int main(int argc, char *argv[])
{
	int c;
	while ((c = getopt_long(argc, argv, "i:p:m:t:s", server_options, NULL)) != -1) {
		switch (c) {
		case 'i':
			server_ip = optarg;
			break;
		case 'p':
			server_port = optarg;
			break;
		case 'm':
			server_map = optarg;
			break;
		case 't':
			server_timeout = optarg;
			break;
		case 's':
			server_log = "/dev/stdout";
			break;
		default:
			exit(-1);
		}
	}

	/* logger setup */
	FILE *log_stream = fopen(server_log, "w+");
	if (log_stream != NULL)
		logger_setlog(log_stream);
	else
		exit(-2);

	return 0;
}
