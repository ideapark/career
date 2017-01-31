#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
        char buf[PATH_MAX];

        (void)getcwd(buf, sizeof(buf));
        printf("Current dir: %s\n", buf);

        printf("Changing to ..\n");
        chdir(".."); /* `cd ..` */

        (void)getcwd(buf, sizeof(buf));
        printf("Current dir is now: %s\n", buf);

        return 0;
}
