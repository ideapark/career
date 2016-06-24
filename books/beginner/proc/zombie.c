#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;
    char *message;
    int n, exit_code;

    printf("fork program starting\n");
    pid = fork();

    switch (pid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            message = "This is the child";
            n = 3;
            exit_code = 37;
            break;
        default:
            message = "This is the parent";
            n = 10;
            exit_code = 0;
            break;
    }

    while (n > 0) {
        puts(message);
        sleep(1);
        n--;
    }

    if (pid != 0) {
        int stat_val;
        pid_t child_pid;

        child_pid = wait(&stat_val);
        printf("Child has finished: PID = %d\n", child_pid);
        if (WIFEXITED(stat_val))
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        else
            printf("Child ternimated abnormally\n");
    }

    return exit_code;
}
