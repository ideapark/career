#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
        int data_processed;
        int file_pipes[2];
        const char some_data[] = "a quick fox jumped over the lazy day.";
        char buffer[BUFSIZ+1];
        pid_t fork_result;

        memset(buffer, '\0', sizeof(buffer));

        if (pipe(file_pipes) == 0) {
                fork_result = fork();
                switch (fork_result) {
                case -1: /* error */
                        fprintf(stderr, "Fork failure");
                        exit(EXIT_FAILURE);
                case 0:  /* child process */
                        sprintf(buffer, "%d", file_pipes[0]);
                        (void)execl("exec", "exec", buffer, (char *)0);
                        exit(EXIT_FAILURE); /* would *NOT* be here */
                default: /* parent process */
                        data_processed = write(file_pipes[1], some_data,
                                               strlen(some_data));
                        printf("%d - wrote %d bytes: %s\n", getpid(), data_processed,
                               some_data);
                        exit(EXIT_SUCCESS);
                }
        } else {
                fprintf(stderr, "pipe() failed.\n");
                exit(EXIT_FAILURE);
        }
}
