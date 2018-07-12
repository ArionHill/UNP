#include "echo.h"
void str_echo(int connfd){
    ssize_t n;
    char buf[MAXLINE];
    long arg1, arg2;

again:
    // while ((n = readline(connfd, buf, MAXLINE)) > 0){
    while ((n = read(connfd, buf, MAXLINE)) > 0){
        
        // if (sscanf(buf, "%ld%ld", &arg1, &arg2) == 2){
        //     snprintf(buf, sizeof(buf), "%ld\n", arg1 + arg2);
        // }else{
        //     snprintf(buf, sizeof(buf), "input error\n");
        // }
        // n = strlen(buf);
        write(connfd, buf, n);
    }
    if (n < 0 && errno == EINTR){
        goto again;
    }
    else if (n < 0){
        perror("str_echo: read error");
    }

}