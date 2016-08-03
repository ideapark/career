#include "map.h"
#include "server.h"

/* map point */
static const char *BRICK = "#";
static const char *IRON  = "@";
static const char *RIVER = "~";
static const char *COIN  = "12345";
static const char *STAR  = "*";
static const char *AREA  = "-";

static char map[Y_MAX][X_MAX] = {AREA};

int load(const char *map)
{
	return 1;
}
