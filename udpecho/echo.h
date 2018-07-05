#include <limits.h>
#include <math.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stropts.h>
#include <sys/wait.h>
// #include <readline/readline.h>

#define SERV_PORT 9877
#define MAXLINE 2048
#ifndef OPEN_MAX
    // #define OPEN_MAX sysconf(_SC_OPEN_MAX)
    #define OPEN_MAX 1024
#endif
#ifndef INFTIM
    #define INFTIM -1
#endif

void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen);
void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen);