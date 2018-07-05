#include "echo.h"

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr,  cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    return 0;
}
