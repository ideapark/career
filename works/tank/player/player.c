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
static const char *player_log = "ply.log";

static struct option player_options[] = {
	{"ip",     required_argument, 0, 'i'},
	{"port",   required_argument, 0, 'p'},
	{"stdout", no_argument,       0, 's'},
	{0,        0,                 0,   0}
};

static int sockfd = -1;
static short teamid = -1;

static int do_gamestart(cJSON *body)
{
	logger_error("%s\n", "player: game start.");
	cJSON *id = cJSON_GetObjectItem(body, "id");
	if (id->type == cJSON_Number) {
		teamid = id->valueint;
	} else {
		logger_error("%s\n", "game start get my team id error.");
		return -1;
	}
	/*
	 * register player's team name
	 */
	cJSON *root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "id", teamid);
	cJSON_AddItemToObject(root, "name", cJSON_CreateString(TEAMNAME));
	char *msg;
	size_t len;
	msg = cJSON_PrintUnformatted(root);
	len = strlen(msg);
	if (write(sockfd, msg, len) < 0)
		logger_error("player: team %hi, broken socket.\n", teamid);
	cJSON_Delete(root);
	return 0;
}

static int do_gameover(cJSON *body)
{
	logger_error("%s\n", "player: game over.");
	cJSON *message = cJSON_GetObjectItem(body, "message");
	if (message->type == cJSON_String)
		logger_info("player: team %hi, game over: %s\n", teamid,
			    message->valuestring);
	else
		logger_error("player: team %hi, %s\n", teamid,
			     "server said game over but did not say goodby.");
	return 0;
}

static int do_legstart(cJSON *body)
{
	logger_warn("%s\n", "player: leg start.");
	return 0;
}

static int do_legend(cJSON *body)
{
	logger_warn("%s\n", "player: leg end.");
	return 0;
}

static int do_roundstep(cJSON *body)
{
	logger_info("%s\n", "player: round step.");
	/* get server status */

	/* calc my action strategy */

	/* echo server my actions */
	cJSON *root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "id", teamid);
	char *msg;
	size_t len;
	msg = cJSON_PrintUnformatted(root);
	len = strlen(msg);
	if (write(sockfd, msg, len) < 0)
		logger_error("player: team %hi, broken socket.\n", teamid);
	cJSON_Delete(root);
	return 1;
}

int main(int argc, char *argv[])
{
	int c;
	while ((c = getopt_long(argc, argv, "i:p:s", player_options, NULL)) != -1) {
		switch (c) {
		case 'i':
			server_ip = optarg;
			break;
		case 'p':
			server_port = optarg;
			break;
		case 's':
			player_log = "/dev/stdout";
			break;
		default:
			exit(-1);
		}
	}

	/* logger setup */
	if (!logger_open(player_log))
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
		if (cJSON_HasObjectItem(root, "head") && cJSON_HasObjectItem(root, "body")) {
			head = cJSON_GetObjectItem(root, "head");
			body = cJSON_GetObjectItem(root, "body");
		} else {
			logger_error("%s\n", "server JSON message protocol error.");
			cJSON_Delete(root);
			break;;
		}
		if (strcmp(head->valuestring, GAME_START) == 0)
			do_gamestart(body);
		else if (strcmp(head->valuestring, LEG_START) == 0)
			do_legstart(body);
		else if (strcmp(head->valuestring, ROUND_STEP) == 0)
			do_roundstep(body);
		else if (strcmp(head->valuestring, LEG_END) == 0)
			do_legend(body);
		else if (strcmp(head->valuestring, GAME_OVER) == 0) {
			do_gameover(body);
			cJSON_Delete(root);
			break;
		} else {
			logger_error("%s\n", "server JSON message head type invalid.");
			cJSON_Delete(root);
			break;
		}
		cJSON_Delete(root);
	}
	close(sockfd);

	return 0;
}
