#include "echo.h"
void str_echo(int connfd){
    ssize_t n;
    char buf[MAXLINE];

again:
    while ((n = read(connfd, buf, MAXLINE)) > 0){
        write(connfd, buf, n);
    }
    if (n < 0 && errno == EINTR){
        goto again;
    }
    else if (n < 0){
        perror("str_echo: read error");
    }

}