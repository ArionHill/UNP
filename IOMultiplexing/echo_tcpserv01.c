#include "echo.h"

int main(int argc, char const *argv[])
{
    int listenfd, connfd, serv_len, cli_len;
    pid_t child_pid;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr, cliaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    serv_len = sizeof(servaddr);
    if (bind(listenfd, (struct sockaddr *)&servaddr, serv_len) != 0){
        perror("bind error");
    }

    listen(listenfd, 5);
    signal(SIGCHLD, sig_chld); // 处理僵死进程
    while (1){
        cli_len = sizeof(cliaddr);
        sleep(20);
        printf("will accept\n");
        connfd = accept(listenfd, (struct sockaddr *)& cliaddr, &cli_len);
        printf("accept\n");
        // if ((child_pid = fork()) == 0){
        //     close(listenfd);
        //     str_echo(connfd);
        //     exit(0);
        // }
        close(connfd);
    }
    return 0;
}
