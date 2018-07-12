#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
// #include <sys/types.h>



#define SERV_PORT 9877
#define	MAXLINE		4096	/* max text line length */
#define	SCTP_MAXLINE	800
#define SERV_MAX_SCTP_STRM	10	/* normal maximum streams */

void sctpstr_cli(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen);
void sctpstr_cli_echoall(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen);