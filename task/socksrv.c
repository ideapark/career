/*
 * A simple server program. It sets up a TCP port for the client
 * program to connect to.
 *
 * This version creates lots and lots of threads withou bound.
 * Maybe even too many threads (when the delay is long). Scopy
 * is PROCESS local to emphasize how bad it can get.
 */

#define _POSIX_C_SOURCE  199506L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/uio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

struct request_struct {
    int                   socket_fd;
    char                  *buf;
    pthread_t             tid;
    struct request_struct *next;
};

typedef struct request_struct request_t;

pthread_attr_t  attr;
int             TCP_PORT = 6500;
int             SLEEP = 10;
int             SPIN = 0;
int             SPAWN = 1;

void count_threads(int i)
{
    static int count = 0, old_count = 0, max_count = 0;
    static pthread_mutex_t count_lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&count_lock);
    count += i;
    if (i == 0)
        printf("Max thread count: %d\n", max_count);
    if (abs(count - old_count) > 9) {
        printf("%d threads running\n", count);
        old_count = count;
    }
    if (count > max_count)
        max_count = count;
    pthread_mutex_unlock(&count_lock);
}

void count_requests(int i)
{
    static int count = 0, old_count = 0, max_count = 0;
    static pthread_mutex_t count_lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&count_lock);
    count += i;
    if (i == 0)
        printf("Max thread count: %d\n", max_count);
    if (abs(count - old_count) > 999) {
        printf("Processed %d requests.\n", count);
        old_count = count;
    }
    if (count > max_count)
        max_count = count;
    pthread_mutex_unlock(&count_lock);
}

void *process_request(void *arg)
{
    char obuf[128];
    request_t *request = (request_t *)arg;
    pthread_t tid = pthread_self();

    DEBUG(printf("[%s] received: \"%s\"\n", thread_name(tid), request->buf));
    delay(SLEEP, SPIN);

    /* Typical msg: "Server[T@9] "DATA SEGMENT 693 [T@r]" */
    sprintf(obuf, "Server[%s] %s", thread_name(tid), request->buf);
    write(request->socket_fd, obuf, 50);
    free(request->buf);
    free(request);
    return NULL;
}

void *process_request_thr(void *arg)
{
    process_request(arg);
    count_threads(-1);
    pthread_exit(NULL);
}

request_t *get_request(int socket_fd)
{
    request_t *request;
    char      ibuf[128];

    read(socket_fd, ibuf, 50);
    if (strcmp(ibuf, "End") == 0)
        return NULL;

    request = (request_t *)malloc(sizeof(request_t));
    request->socket_fd = socket_fd;
    request->buf = (char *)malloc(strlen(ibuf)+1);
    strcpy(request->buf, ibuf);
    count_requests(1);
    return request;
}

void producer(int socket_fd)
{
    request_t *request;
    pthread_t tid;

    while (1) {
        request = get_request(socket_fd);
        if (request == NULL)
            return;
        if (SPAWN == 0)
            process_request(request);
        else {
            pthread_create(&tid, &attr, process_request_thr, (void *)request);
            count_threads(1);
        }
    }
}

void *accept_requests(void *arg)
{
    int socket_fd = (int)arg;
    char ibuf[128], obuf[128];
    int i, j;
    pthread_t tid = pthread_self();
    char *name = thread_name(tid);

    printf("[%s] Accepting on socket: %d\n", name, socket_fd);

    producer(socket_fd);
    write(socket_fd, "End", 4);
    close(socket_fd);
    count_threads(-1);
    printf("[%s] Done Processing.", thread_name(tid));
    count_threads(0);
    pthread_exit(NULL);
}

void *killer(void *arg)
{
    sleep(30);
    exit(NULL);
}

int main(int argc, char *argv[])
{
    int i, sockfd, newsockfd, clilen;
    struct sockaddr_in cli_addr, srv_addr;
    pthread_t tid;

    if (argc >= 2)
        TCP_PORT = atoi(argv[1]);
    if (argc >= 3)
        SLEEP = atoi(argv[2]);
    if (argc >= 4)
        SPIN = atoi(argv[3]);
    if (argc >= 4)
        SPAWN = atoi(argv[4]);
    printf("TCP_PORT = %d SLEEP (ms) = %d SPIN (us) = %d SPAWN = %d\n",
            TCP_PORT, SLEEP, SPIN, SPAWN);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "server: can't open stream socket\n");
        exit(0);
    }
    memset((char *)&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_addr.sin_port = htons(TCP_PORT);

    if (bind(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0) {
        fprintf(stderr, "server: can't bind local address\n");
        exit(0);
    }

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&tid, &attr, killer, NULL);

    listen(sockfd, 5);

    while (1) {
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr,, &clilen);
        if (newsockfd < 0) {
            fprintf(stderr, "server: accept error\n");
            exit(0);
        }

        pthread_create(&tid, &attr, accept_requests, (void *)newsockfd);
        count_threads(1);
    }
    return 0;
}
