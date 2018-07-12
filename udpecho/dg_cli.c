#include "echo.h"

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    
    while (fgets(sendline, MAXLINE, fp) != NULL){
        sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
}


/**
 * dg_cli_addr: 验证返回的套接字地址的dg_cli函数版本
 */
void dg_cli_addr(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    socklen_t len;
    struct sockaddr *preply_addr;
    preply_addr = malloc(servlen);
    while (fgets(sendline, MAXLINE, fp) != NULL) {
        sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        len = servlen;
        n = recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);               // 通知内核返回数据报发送者的地址.
        if (len != servlen || memcmp(pservaddr, preply_addr, len) != 0){
            printf("reply from %s (ignored)\n", Sock_ntop(preply_addr, len));
            continue;
        }
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
}


/**
 * 调用connect的dg_cli函数
 */
void dg_cli_conn(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    connect(sockfd, (struct sockaddr *)pservaddr, servlen);

    while (fgets(sendline, MAXLINE, fp) != NULL){
        write(sockfd, sendline, strlen(sendline));

        n = read(sockfd, recvline, MAXLINE);

        recvline[n] = 0;
        fputs(recvline, stdout);
    }
}


/**
 * dg_cli_NDG写固定数目的数据报到服务器
 */
#define NDG     2000
#define DGLEN   1400
void dg_cli_NDG(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
    int i;
    char sendline[DGLEN];
    for (i = 0; i < NDG; ++ i){
        sendto(sockfd, sendline, DGLEN, 0, pservaddr, servlen);
    }
}