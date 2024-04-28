#
# echo - print command-line arguments
#
BEGIN {
    for (i = 1; i < ARGC; i++)
	printf("%s\n", ARGV[i])
}
