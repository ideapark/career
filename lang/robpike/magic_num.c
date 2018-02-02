enum {
	MINROW      = 1,                /* top edge */
	MINCOL      = 1,                /* left edge */
	MAXROW      = 24,               /* bottom edge (<=) */
	MAXCOL      = 80,               /* right edge (<=) */
	LABELROW    = 1,                /* position of labels */
	NLET        = 26,               /* size of alphabet */
	HEIGHT      = MAXROW - 4,       /* height of bars */
	WIDTH       = (MAXCOL-1)/NLET   /* width of bars */
};

fac = (lim + HEIGHT-1)/HEIGHT; /* set scale factor */
if (fac < 1)
	fac = 1;

for (i = 0; i < NLET; i++) { /* generate histogram */
	if (let[i] == 0)
		continue;
	for (j = HEIGHT-let[i]/fac; j < HEIGHT; j++)
		draw(j+1+LABELROW, (i+1)*WIDTH, '*');
 }
draw(MAXROW-1, MINCOL+1, ' '); /* label x axis */

for (i = 'A'; i <= 'Z'; i++)
	printf("%c ", i);
