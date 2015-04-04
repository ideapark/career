#include <getopt.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int c;
    int do_all, do_help, do_verbose; /* flag variables */
    char *myfile = NULL;
    char *user = NULL;
    struct option longopts[] = {
        {"all", no_argument, &do_all, 1},
        {"file", required_argument, NULL, 'f'},
        {"help", no_argument, &do_help, 1},
        {"verbose", no_argument, &do_verbose, 1},
        {"user", optional_argument, NULL, 'u'},
        {0, 0, 0, 0}
    };

    while ((c = getopt_long(argc, argv, ":ahvf:u::W;", longopts, NULL)) != -1) {
        switch (c) {
            case 'a':
                do_all = 1;
                break;
            case 'f':
                myfile = optarg;
                break;
            case 'h':
                do_help = 1;
                break;
            case 'u':
                if (optarg != NULL)
                    user = optarg;
                else
                    user = "root";
                break;
            case 'v':
                do_verbose = 1;
                break;
            case 0: /* getopt_long() set a variable, just keep going */
                break;
#if 0
            case 1:
                /*
                 * Use this case if getopt_long() should go through all
                 * arguments. If so, add a leading '-' character to optstring.
                 * Actual code, if any, goes there.
                 */
                break;
#endif
            case ':': /* missing option argument */
                fprintf(stderr, "%s: option '%c' requires an argument\n",
                        argv[0], optopt);
                break;
            case '?':
            default: /* invalid option */
                fprintf(stderr, "%s: option '%c' is invalid: ignored\n",
                        argv[0], optopt);
                break;
        }
    }

    printf("do_all: %d\n", do_all);
    printf("do_help: %d\n", do_help);
    printf("do_verbose: %d\n", do_verbose);
    printf("myfile: %s\n", myfile);
    printf("user: %s\n", user);

    return 0;
}
