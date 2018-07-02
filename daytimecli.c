#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>

#include "err.h"

#define MAXLINE 80

int main(int argc, char **argv){
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 2){
        print_err("usage: a.out ip_addr");
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        print_err("socket error!");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    // servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if ((inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) <= 0){
        print_err("inet_pton error for %s", argv[1]);
    }

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("connect error");
    }
    
    while ((n = read(sockfd, recvline, MAXLINE)) > 0){
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF){
            print_err("fputs error");
        }
    }
    if (n < 0){
        print_err("read error");
    }
    exit(0);
}
