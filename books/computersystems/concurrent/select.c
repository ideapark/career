#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int listenfd, connfd, port;
	socklen_t clientlen = sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr;
	fd_set read_set, ready_set;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		return 0;
	}

	port = atoi(argv[1]);
	listenfd = open_listenfd(port);

	FD_ZERO(&read_set);
	FD_SET(STDIN_FILENO, &read_set);
	FD_SET(listenfd, &read_set);

	while (1) {
		read_set = read_set;
		select(listenfd+1, &read_set, NULL, NULL, NULL);
		if (FD_ISSET(STDIN_FILENO, &ready_set))
			printf("OK: ready to read.\n");
		if (FD_ISSET(listenfd, &ready_set)) {
			connfd = accept(listenfd,
					(struct sockaddr *)&clientaddr,
					&clientlen);
			printf("OK: connect file descriptor: %d.\n", connfd);
			close(connfd);
		}
	}
	return 0;
}
