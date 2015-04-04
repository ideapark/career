#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "A quick fox jumped over a lazy dog.";
    char buffer[BUFSIZ+1];
    pid_t fork_result;

    memset(buffer, '\0', sizeof(buffer));

    if (pipe(file_pipes) == 0) {
        fork_result = fork();
        switch (fork_result) {
            case -1:
                fprintf(stderr, "Fork failure");
                exit(EXIT_FAILURE);
            case 0:  /* parent process */
                data_processed = read(file_pipes[0], buffer, BUFSIZ);
                printf("Process: %d read %d bytes: %s\n", getpid(),
                        data_processed, buffer);
                exit(EXIT_SUCCESS);
            default: /* child process */
                data_processed = write(file_pipes[1], some_data, strlen(some_data));
                printf("Process: %d write %d bytes: %s\n", getpid(),
                        data_processed, some_data);
                exit(EXIT_SUCCESS);
        }
    } else {
        fprintf(stderr, "pipe() failed.\n");
        exit(EXIT_FAILURE);
    }
}
