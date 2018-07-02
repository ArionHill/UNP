#include "echo.h"

void str_cli(FILE *fp, int sockfd){
    char sendline[MAXLINE], recvline[MAXLINE];

    while (fgets(sendline, MAXLINE, fp) != NULL){
        write(sockfd, sendline, strlen(sendline));
        if (readline(sockfd, recvline, MAXLINE) == 0){
            perror("str_lic: server terminated prematurely");
        }
        fputs(recvline, stdout);
    }
}

void str_cli_SIGPIPE(FILE *fp, int sockfd){
    char sendline[MAXLINE], recvline[MAXLINE];

    while (fgets(sendline, MAXLINE, fp) != NULL){
        if (write(sockfd, sendline, 1) != 1){
            perror("wirte error");
        }
        sleep(1);
        if (write(sockfd, sendline + 1, strlen(sendline) - 1) != strlen(sendline) - 1){
            perror("write error");
        }
        if (readline(sockfd, recvline, MAXLINE) == 0){
            perror("str_lic_SIGPIPE: server terminated prematurely");
        }
        fputs(recvline, stdout);
    }
}

ssize_t readline(int fd, void *vptr, size_t maxlen){
    ssize_t n, rc;
    char c, *ptr;

    ptr = vptr;
    for (n = 1; n < maxlen; n ++){
    again:
        if ((rc = read(fd, &c, 1)) == 1){
            *ptr++ = c;
            if (c == '\n'){
                break;
            }
        }else if (rc == 0){
            *ptr = 0;
            return (n - 1);
        }else{
            if (errno == EINTR){
                goto again;
            }
            return -1;
        }
    }
    *ptr = 0;
    return n;
}