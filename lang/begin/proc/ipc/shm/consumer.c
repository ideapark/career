#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "shm_com.h"

int main(void)
{
    int shmid;
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;

    srand((unsigned int)getpid());

    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);
    if (shmid == -1) {
        fprintf(stderr, "%d :- shmget failed\n", getpid());
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "%d :- shmat failed\n", getpid());
        exit(EXIT_FAILURE);
    }

    printf("%d :- memory attached at %X\n", getpid(), (unsigned int)shared_memory);

    shared_stuff = (struct shared_use_st *)shared_memory;
    shared_stuff->written_by_you = 0;

    while (running) {
        if (shared_stuff->written_by_you) {
            printf("%d :- you wrote: %s", getpid(), shared_stuff->some_text);
            sleep(rand()%4); /* make the other process wait for us! */
            shared_stuff->written_by_you = 0;
            if (strncmp(shared_stuff->some_text, "end", 3) == 0)
                running = 0;
        }
    }

    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "%d :- shmdt failed\n", getpid());
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "%d :- shmctl(IPC_RMID) failed\n", getpid());
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
