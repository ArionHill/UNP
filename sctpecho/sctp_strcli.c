#include "sctpecho.h"

void sctpstr_cli(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen){
    struct sockaddr_in peeraddr;
    struct sctp_sndrcvinfo sri;
    char sendline[MAXLINE], recvline[MAXLINE];
    socklen_t len;
    int out_sz, rd_sz;
    int msg_flags;

    bzero(&sri, sizeof(sri));
    while (fgets(sendline, MAXLINE, fp) != NULL){
        if (sendline[0] != '['){
            printf("Error, line must be of the form '[streamnum]text'\n");
            continue;
        }
        sri.sinfo_stream = strtol(&sendline[1], NULL, 0);
        printf("buf[1]: %c, sinfo_stream: %d\n", sendline[1], sri.sinfo_stream);
        out_sz = strlen(sendline);
        sctp_sendmsg(sock_fd, sendline, out_sz,
                    to, tolen, 0, 0, sri.sinfo_stream, 0, 0);
        len = sizeof(peeraddr);
        rd_sz = sctp_recvmsg(sock_fd, recvline, sizeof(recvline),
                            (struct sockaddr *)&peeraddr, &len, &sri, &msg_flags);
        printf("From str:%d seq:%d (assoc:0x%x):",
                sri.sinfo_stream, sri.sinfo_ssn, (u_int)sri.sinfo_assoc_id);
        printf("%.*s", rd_sz, recvline);
    }
}

void sctpstr_cli_echoall(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen){
    struct sockaddr_in peeraddr;
    struct sctp_sndrcvinfo sri;
    char sendline[SCTP_MAXLINE], recvline[SCTP_MAXLINE];
    socklen_t len;
    int strsz, i, rd_sz;
    int msg_flags;

    bzero(sendline, sizeof(sendline));
    bzero(&sri, sizeof(sri));
    while (fgets(sendline, SCTP_MAXLINE - 9, fp) != NULL){
        strsz = strlen(sendline);
        if (sendline[strsz-1] == '\n'){
            sendline[strsz-1] = '\0';
            strsz --;
        }
        for (i = 0; i < SERV_MAX_SCTP_STRM; i ++){
            snprintf(sendline + strsz, sizeof(sendline) - strsz,
                    ".msg.%d", i);
            sctp_sendmsg(sock_fd, sendline, sizeof(sendline),
                    to, tolen, 0, 0, i, 0, 0);
        }
        
        for (i = 0; i < SERV_MAX_SCTP_STRM; i ++){
            len = sizeof(peeraddr);
            rd_sz = sctp_recvmsg(sock_fd, recvline, sizeof(recvline),
                                (struct sockaddr *)&peeraddr, &len, &sri, &msg_flags);
            printf("From str:%d seq:%d (assoc:0x%x):",
                    sri.sinfo_stream, sri.sinfo_ssn, (u_int)sri.sinfo_assoc_id);
            printf("%.*s", rd_sz, recvline);
        }        
    }
}