#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define ONE_K (1024)

int main(void) {
    char *some_memory;
    size_t size_to_allocate = ONE_K;
    int megs_obtained = 0;
    int ks_obtained = 0;

    while (1) {
        for (ks_obtained = 0; ks_obtained < 1024; ks_obtained++) {
            some_memory = (char *)malloc(size_to_allocate);
            if (some_memory == NULL)
                return EXIT_FAILURE;
            else
                sprintf(some_memory, "Hello, World");
        }
        megs_obtained++;
        printf("Mow allocated %d Megabytes\n", megs_obtained);
    }
    return EXIT_SUCCESS;
}
