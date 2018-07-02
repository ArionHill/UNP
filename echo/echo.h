#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
// #include <readline/readline.h>

#define SERV_PORT 9877
#define MAXLINE 2048

void str_echo(int);
void str_cli(FILE *fp, int sockfd);
void str_cli_SIGPIPE(FILE *fp, int sockfd);
ssize_t readline(int fd, void *vptr, size_t maxlen);
void sig_chld(int signo);
