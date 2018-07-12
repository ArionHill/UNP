#include "sctpecho.h"

int main(int argc, char const *argv[])
{
    int sock_fd;
    struct sockaddr_in servaddr;
    struct sctp_event_subscribe evnts;
    int echo_to_all = 0;

    if (argc < 2){
        perror("Missing host argument - use 'sctpcli host'\n");
        exit(1);
    }
    if (argc > 2){
        printf("Echoing message to all streams\n");
        echo_to_all = 1;
    }

    sock_fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    bzero(&evnts, sizeof(evnts));
    evnts.sctp_data_io_event = 1;
    setsockopt(sock_fd, IPPROTO_SCTP, SCTP_EVENTS, &evnts, sizeof(evnts));
    if (echo_to_all == 0)
        sctpstr_cli(stdin, sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    else
        sctpstr_cli_echoall(stdin, sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    close(sock_fd);
    return 0;
}
