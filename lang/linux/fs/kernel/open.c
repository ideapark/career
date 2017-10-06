#include <unistd.h>
#include <fcntl.h>

int main(void)
{
        if (open("open_test.txt", O_CREAT, S_IRUSR|S_IXOTH) == -1)
                write(2, "create file error\n", 18);
        return 0;
}
