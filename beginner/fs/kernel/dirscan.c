#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir, int depth) {
    DIR *pdir;
    struct dirent *pentry;
    struct stat statbuf;

    if ((pdir = opendir(dir)) == NULL) {
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while ((pentry = readdir(pdir)) != NULL) {
        lstat(pentry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode)) {
            /* found a directory, but ignore . and .. */
            if (strcmp(".", pentry->d_name) == 0 || strcmp("..", pentry->d_name) == 0)
                continue;
            printf("%*s%s/\n", depth, "", pentry->d_name);
            /* recurse at a new indent level */
            printdir(pentry->d_name, depth+4);
        } else {
            printf("%*s%s\n", depth, "", pentry->d_name);
        }
    }
    chdir("..");
    closedir(pdir);
}

int main(int argc, char *argv[]) {
    char *topdir = ".";
    if (argc >= 2)
        topdir = argv[1];
    printf("Directory of scan of %s:\n", topdir);
    printdir(topdir, 0);
    printf("done.\n");
    return 0;
}
