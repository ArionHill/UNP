#include "echo.h"

void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
    int n;
    socklen_t len;
    char mesg[MAXLINE];

    for ( ; ; ){
        len = clilen;
        n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        sendto(sockfd, mesg, n, 0, pcliaddr, len);
    }
}


/**
 * 
 */
static void recvfrom_int(int);
static int  count;

void dg_echo_cnt(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
    int n;
    socklen_t len;
    char mesg[MAXLINE];

    signal(SIGINT, recvfrom_int);

    n = 256 * 1024;

    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n));

    int val;
    int vallen = sizeof(val);
    int buflen = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &val, &vallen);
    printf("buf: %d, val: %d\n", buflen, val);

    for ( ; ; ){
        len = clilen;
        recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

        count ++;
    }
}

static void recvfrom_int(int signo)
{
    printf("\nreceived %d datagrams\n", count);
    exit(0);
}