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

void str_echo(int);
void str_cli(FILE *fp, int sockfd);
void str_cli_SIGPIPE(FILE *fp, int sockfd);
void str_cli_slct(FILE *fp, int sockfd);
void str_cli_slct_shtdwn(FILE *fp, int sockfd);
ssize_t readline(int fd, void *vptr, size_t maxlen);
void sig_chld(int signo);
