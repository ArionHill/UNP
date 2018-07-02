#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <time.h>


int main(int argc, char const *argv[])
{
    int listenfd, connfd, server_len, client_len;
    struct sockaddr_in servaddr, cliaddr;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   
    servaddr.sin_port = htons(13);

    server_len = sizeof(servaddr);
    if (bind(listenfd, (struct sockaddr *)&servaddr, server_len) != 0) {
        perror("bind error");
    }
    listen(listenfd, 5);
    
    while (1){
        client_len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &client_len);
        char buff[INET_ADDRSTRLEN];
        printf("connection from %s, port %d\n",
                inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
                ntohs(cliaddr.sin_port));
        
        time_t ticks;
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        write(connfd, buff, strlen(buff));
        close(connfd);
    }
    return 0;
}
