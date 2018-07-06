#include "echo.h"

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2){
        fprintf(stderr, "usage: udpcli <IP address>");
        exit(1);
    }
    servaddr.sin_family = AF_INET;
    // servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_port = htons(7);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    dg_cli_addr(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    return 0;
}
