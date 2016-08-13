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
#include "cJSON.h"

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

static int do_gamestart(cJSON *body)
{
	return 0;
}

static int do_gameover(cJSON *body)
{
	return 0;
}

static int do_legstart(cJSON *body)
{
	return 0;
}

static int do_legend(cJSON *body)
{
	return 0;
}

static int do_roundstep(cJSON *body)
{
	return 1;
}

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

	char buf[BUFFER_MAX+1] = {'\0'};
	while (read(sockfd, buf, BUFFER_MAX) > 0) {
		cJSON *root = cJSON_Parse(buf);
		if (root == NULL) {
			logger_error("%s\n", "server JSON message invalid.");
			break;
		}
		cJSON *head, *body;
		if (cJSON_HasObjectItem(root, "head") &&
		    cJSON_HasObjectItem(root, "body")) {
			head = cJSON_GetObjectItem(root, "head");
			body = cJSON_GetObjectItem(root, "body");
		} else {
			cJSON_Delete(root);
			continue;
		}
		if (strcmp(head->valuestring, GAME_START) == 0)
			do_gamestart(body);
		else if (strcmp(head->valuestring, GAME_OVER) == 0)
			do_gameover(body);
		else if (strcmp(head->valuestring, LEG_START) == 0)
			do_legstart(body);
		else if (strcmp(head->valuestring, LEG_END) == 0)
			do_legend(body);
		else if (strcmp(head->valuestring, ROUND_STEP) == 0)
			do_roundstep(body);
		else
			logger_error("%s\n", "server JSON message head type error.");
		cJSON_Delete(root);
	}

	return 0;
}
