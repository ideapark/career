#define N 5                  /* number of philosophers */
#define LEFT  (i-1+N) % N    /* i's left neighbor */
#define RIGHT (i+1) % N      /* i's right neighbor */
#define THINKING 0           /* philosopher thinking */
#define HUNGRY   1           /* philosopher want to get fork */
#define EATING   2           /* philosopher eating */

typedef int semaphore;
int state[N];                /* array of philosopher's state */
semaphore mutex = 1;         /* critical area */
semaphore s[N];              /* semaphore for each philosopher */

void philosopher(int i)
{
	while (1) {
		think();             /* thinking */
		take_forks(i);       /* get two forks or blocked */
		eat();               /* eating */
		put_forks(i);        /* put back two forks */
	}
}

void take_forks(int i)
{
	down(&mutex);            /* enter critical area */
	state[i] = HUNGRY;       /* philosopher i is hungry */
	test(i);                 /* try to get two forks */
	up(&mutex);              /* leave critical area */
	down(&s[i]);             /* cannot get two forks, blocked */
}

void put_forks(int i)
{
	down(&mutex);            /* enter critical area */
	state[i] = THINKING;     /* finishing eating */
	test(LEFT);              /* test left neighbor can eating */
	test(RIGHT);             /* test right neighbor can eating */
	up(&mutex);              /* leave critical area */
}

void test(i)
{
	if (state[i] == HUNGRY &&
	    state[LEFT] != EATING &&
	    state[RIGHT] != EATING) {
		state[i] = EATING;
		up(&s[i]);
	}
}

int think(void)
{
	printf("philosopher thinking...\n");
}

int eat(void)
{
	printf("philosopher eating...\n");
}
