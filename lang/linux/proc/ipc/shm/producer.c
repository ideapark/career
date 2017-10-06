#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "shm_com.h"

int main(void)
{
        int running = 1;
        int shmid;
        char buffer[BUFSIZ];
        void *shared_memory = (void *)0;
        struct shared_use_st *shared_stuff;

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

        printf("%d :- memory attached at %X\n", getpid(),
               (unsigned int)shared_memory);

        shared_stuff = (struct shared_use_st *)shared_memory;

        while (running) {
                while (shared_stuff->written_by_you == 1) {
                        sleep(1);
                        printf("%d :- waiting for client...\n", getpid());
                }
                printf("%d :- enter some text: ", getpid());
                fgets(buffer, BUFSIZ, stdin);
                strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
                shared_stuff->written_by_you = 1;
                if (strncmp(buffer, "end", 3) == 0)
                        running = 0;
        }

        if (shmdt(shared_memory) == -1) {
                fprintf(stderr, "%d :- shmdt failed\n", getpid());
                exit(EXIT_FAILURE);
        } else {
                exit(EXIT_SUCCESS);
        }
}
