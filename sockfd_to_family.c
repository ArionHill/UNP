#include <netinet/in.h>

int sockfd_to_family(int sockfd){
    struct sockaddr_storage ss; // 因为套接字不知道要分配的套接字地址结构的类型, 采用sockaddr_storage 套接字地址通用结构.
    socklen_t len;

    len = sizeof(ss);
    if (getsockname(sockfd, (struct sockaddr *)&ss, &len) < 0){
        return -1;
    }
    return ss.ss_family;
}