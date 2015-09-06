#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int len;
    int sockfd;
    int result;
    char ch = 'A';
    struct sockaddr_un address;

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("oops: client.");
        exit(1);
    }

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("%d :- char from server = %c\n", getpid(), ch);
    close(sockfd);

    exit(0);
}
