#include <unistd.h>    // NOTE: unistd.h must be at first
			// POSIX flag defined may impact
			// other include file
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char block[512]; // 8 256 1024 can be funny
	int in, out;
	int nread;

	if (argc != 3) {
		write(2, "usage: copy from to\n", 20);
		exit(-1);
	}

	if ((in = open(argv[1], O_RDONLY)) == -1) {
		write(2, "open from file failed.\n", 23);
		exit(-2);
	}

	if ((out = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR)) == -1) {
		write(2, "open to file failed.\n", 21);
		exit(-2);
	}

	while ((nread = read(in, block, sizeof(block))) > 0)
		write(out, block, nread);

	close(in);
	close(out);
	return 0;
}
