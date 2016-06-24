#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Missing required arguments.\n");
        _Exit(-1); /* no signal and no atexit would be called */
    }
    return 0;
}
