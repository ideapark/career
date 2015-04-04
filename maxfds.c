#include <unistd.h>
#include <stdio.h>

int getdtablesize(void);

int main(int argc, char *argv[])
{
    printf("max file descriptors: %d\n", getdtablesize());

    return 0;
}
