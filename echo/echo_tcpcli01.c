#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#include "echo.h"

int main(int argc, char const *argv[])
{
    if (argc != 2){
        fprintf(stderr, "usage: client <ip address>");
        exit(1);
    }
    int i, sockfd[5];
    struct sockaddr_in servaddr;
    for (i = 0; i < 5; ++ i){
        sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

        connect(sockfd[i], (struct sockaddr *)&servaddr, sizeof(servaddr));
    }
    
    str_cli_SIGPIPE(stdin, sockfd[0]);

    return 0;
}
