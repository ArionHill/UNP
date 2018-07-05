#include "echo.h"
#define max(a, b) ( ((a) > (b)) ? (a) : (b))

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

void str_cli_slct(FILE *fp, int sockfd){
    int maxfdp1;
    fd_set rset;
    char sendline[MAXLINE], recvline[MAXLINE];

    FD_ZERO(&rset);
    while (1){
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        select(maxfdp1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset)){
            if (readline(sockfd, recvline, MAXLINE) == 0){
                perror("read error");
                exit(1);
            }
            // freopen("output.txt","a+",stdout);
            fputs(recvline, stdout);
        }
        if(FD_ISSET(fileno(fp), &rset)){
            if (fgets(sendline, MAXLINE, fp) == NULL){
                return;
            }
            write(sockfd, sendline, strlen(sendline));
            sleep(2);
        }
    }

}

void str_cli_slct_shtdwn(FILE *fp, int sockfd){
    int maxfdp1, stdineof;
    fd_set rset;
    char sendline[MAXLINE], recvline[MAXLINE];
    int n;

    stdineof = 0;
    FD_ZERO(&rset);
    while (1){
        if (stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        select(maxfdp1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset)){
            if ((n = read(sockfd, recvline, MAXLINE)) == 0){
                if (stdineof == 1){
                    return;
                }
                perror("read error");
                exit(1);
            }
            write(fileno(stdout), recvline, n);
        }
        if(FD_ISSET(fileno(fp), &rset)){
            if ((n = read(fileno(fp), sendline, MAXLINE)) == 0){
                stdineof = 1;
                shutdown(sockfd, SHUT_WR);
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            // sprintf(sendline, "a"); 
            write(sockfd, sendline, strlen(sendline));
            // sleep(10);
        }
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