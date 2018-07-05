all: server client serverslct serverpoll
server: echo_tcpserv01.c echo.h echo_sigchldwait.c echo_serv_str.c echo_cli_str.c
	gcc -o server echo_tcpserv01.c echo_sigchldwait.c echo_serv_str.c echo_cli_str.c -lm
client: echo_tcpcli01.c echo_cli_str.c echo.h
	gcc -o client echo_tcpcli01.c echo_cli_str.c -lm
serverslct: echo_tcpserv_slct.c echo.h echo_sigchldwait.c echo_serv_str.c echo_cli_str.c
	gcc -o serverslct echo_tcpserv_slct.c echo_sigchldwait.c echo_serv_str.c echo_cli_str.c -lm

serverpoll: echo_tcpserv_poll.c echo.h
	gcc -o serverpoll echo_tcpserv_poll.c