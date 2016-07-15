#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <klee/klee.h>

#define H 7
#define W 11

char maze[H][W] = {
	"+-+---+---+",
	"| |     |#|",
	"| | --+ | |",
	"| |   | | |",
	"| +-- | | |",
	"|     |   |",
	"+-----+---+",
};

void draw()
{
	int i, j;
	for (i = 0; i < H; i++) {
		for (j = 0; j < W; j++)
			printf("%c", maze[i][j]);
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	int x, y; /* player position */
	int ox, oy; /* old player position */
	int i = 0; /* iteration number */
#define ITERS 28
	char program[ITERS];

	x = 1;
	y = 1;
	maze[y][x] = 'X';

	read(0, program, ITERS);

	klee_make_symbolic(program, ITERS, "program");

	while (i < ITERS) {
		ox = x;
		oy = y;
		switch (program[i]) {
		case 'w':
			y--;
			break;
		case 's':
			y++;
			break;
		case 'a':
			x--;
			break;
		case 'd':
			x++;
			break;
		default:
			printf("Wrong command! (only w,s,a,d accepted!)\n");
			printf("You lose!\n");
			exit(-1);
		}
		if (maze[y][x] == '#') {
			printf("You win!\n");
			printf("Your solution %s\n", program);
			exit(0);
		}
		if (maze[y][x] != ' ' && !((y == 2 && maze[y][x] == '|' && x > 0 && x < W))) {
			x = ox;
			y = oy;
		}
		if (ox == x && oy == 6) {
			printf("You lose\n");
			exit(-2);
		}
		maze[y][x] = 'X';
		draw();
		i++;
		sleep(1);
	}
	printf("You lose\n");
	return 0;
}
