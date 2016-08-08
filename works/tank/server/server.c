/*
 * server.c
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "server.h"
#include "logger.h"
#include "map.h"
#include "link.h"

/*
 * server command line arguments
 */
static const char *server_port    = "6000";
static const char *server_map     = "map.txt";
static const char *server_timeout = "400";
static const char *server_log     = "server.log";

static struct option server_options[] = {
	{"port",    required_argument, 0, 'p'},
	{"map",     required_argument, 0, 'm'},
	{"timeout", required_argument, 0, 't'},
	{"stdout",  no_argument,       0, 's'},
	{0,         0,                 0,   0}
};

/*
 * our game
 */
static struct game game;

int main(int argc, char *argv[])
{
	/*
	 * server options
	 */
	int c;
	while ((c = getopt_long(argc, argv, "p:m:t:s", server_options, NULL)) != -1) {
		switch (c) {
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
	if (!logger_open(server_log))
		exit(-2);

	/* load map */
	if (!map_load(server_map))
		exit(-3);

	/*
	 * game initialization
	 */
	game.leg_remain = LEG_MAX;
	game.round_remain = ROUND_MAX;
	short tm, tk;
	for (tm = 0; tm < TEAM_MAX; tm++) {
		game.teams[tm].id = tm;
		game.teams[tm].life_remain = LIFE_MAX;

		for (tk = 0; tk < TANK_MAX; tk++) {
			game.teams[tm].tanks[tk].id = tm * TANK_MAX + tk;
			game.teams[tm].tanks[tk].star_count = 0;

			/* alloc tank postion */
			short y, x;
			for (y = 0; y < Y_MAX; y++) {
				for (x = 0; x < X_MAX; x++) {
					if (map_get(y, x) == AREA) {
						game.teams[tm].tanks[tk].pos.y = y;
						game.teams[tm].tanks[tk].pos.x = x;
						map_set(y, x, TANK);
						goto tank_ok;
					}
				}
			}
			logger_warn("%s\n", "map area less than tanks.");
			exit(-4);
		tank_ok:
			logger_info("team: %hi, tank: %hi, at position (%hi, %hi)\n",
				    game.teams[tm].id,
				    game.teams[tm].tanks[tk].id,
				    game.teams[tm].tanks[tk].pos.y,
				    game.teams[tm].tanks[tk].pos.x);
		}
	}

	logger_close();
	return 0;
}
