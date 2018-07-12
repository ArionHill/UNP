/**
 * UDP中外出接口的确定
 */

#include "echo.h"

int main(int argc, char const *argv[])
{
    int sockfd;
    socklen_t len;
    struct sockaddr_in cliaddr, servaddr;

    if (argc != 2){
        fprintf(stderr, "usgae: udpcli <IP addr>");
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    /**
     * 执行connect时内核选择本地IP,这个本地IP地址通过为目的IP地址搜索路由表得到外出接口,
     * 然后选用该接口的主IP地址而选定.
     */
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    len = sizeof(cliaddr);
    getsockname(sockfd, (struct sockaddr *)&cliaddr, &len);
    printf("local address %s\n", Sock_ntop((struct sockaddr *)&cliaddr, len));
    return 0;
}
