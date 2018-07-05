#include "echo.h"

int main(int argc, char const *argv[])
{
    int i, maxi, listenfd, connfd, sockfd;
    int nready;
    ssize_t n;
    char buf[MAXLINE];
    socklen_t clilen;
    struct pollfd client[OPEN_MAX];
    printf("OPEN_MAX: %ld\n", OPEN_MAX);
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 5);

    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    for (i = 1; i < OPEN_MAX; ++ i){
        client[i].fd = -1;
    }
    maxi = 0;

    while (1){
        nready = poll(client, maxi + 1, INFTIM);
        printf("nready: %d\n", nready);
        if (client[0].revents & POLLRDNORM){
            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

            for (i = 1; i < OPEN_MAX; ++ i){
                if (client[i].fd < 0){
                    client[i].fd = connfd;
                    break;
                }
            }
            if (i == OPEN_MAX){
                fprintf(stderr, "too many clients");
                exit(1);
            }

            client[i].events = POLLRDNORM;
            if (i > maxi){
                maxi = i;
            }
            if (--nready <= 0){
                continue;
            }
        }

        for (i = 1; i <= maxi; ++ i){
            if ((sockfd = client[i].fd) < 0){
                continue;
            }
            if (client[i].revents & (POLLRDNORM | POLLERR)){
                if ((n = read(sockfd, buf, MAXLINE)) < 0){
                    if (errno = ECONNRESET){
                        close(sockfd);
                        client[i].fd = -1;
                    }else{
                        perror("read error");
                    }
                }else if (n == 0){
                    close(sockfd);
                    client[i].fd = -1;
                }else{
                    write(sockfd, buf, n);
                }

                if (--nready <= 0){
                    break;
                }
            }
        }
    }

    return 0;
}
