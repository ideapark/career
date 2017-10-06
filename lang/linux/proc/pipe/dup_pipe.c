#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
        int data_processed;
        int file_pipes[2];
        const char some_data[] = "a quick fox jumped over the lazy dag.";
        pid_t fork_result;

        if (pipe(file_pipes) == 0) {
                fork_result = fork();
                switch (fork_result) {
                case -1: /* error */
                        fprintf(stderr, "Fork failure");
                        exit(EXIT_FAILURE);
                case 0:  /* child process */
                        close(0);
                        dup(file_pipes[0]);
                        close(file_pipes[0]);
                        close(file_pipes[1]);
                        execlp("od", "od", "-c", (char *)0);
                        exit(EXIT_FAILURE); /* would *NOT* be here */
                default: /* parent process */
                        close(file_pipes[0]);
                        data_processed = write(file_pipes[1], some_data,
                                               strlen(some_data));
                        close(file_pipes[1]);
                        printf("%d - wrote %d bytes: %s\n", getpid(), data_processed,
                               some_data);
                        exit(EXIT_SUCCESS);
                }
        } else {
                fprintf(stderr, "Pipe failure.\n");
                exit(EXIT_FAILURE);
        }
}
