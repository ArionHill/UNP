all: server client
server: echo_tcpserv01.c echo.h echo_sigchldwait.c echo_serv_str.c
	gcc -o server echo_tcpserv01.c echo_sigchldwait.c echo_serv_str.c
client: echo_tcpcli01.c echo_cli_str.c echo.h
	gcc -o client echo_tcpcli01.c echo_cli_str.c