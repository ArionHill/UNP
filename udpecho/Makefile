all: udpserv01 udpcli01
udpserv01: udpserv01.o dg_echo.o
udpserv01.o: udpserv01.c echo.h 
dg_echo.o: dg_echo.c echo.h

udpcli01: udpcli01.o dg_cli.o sock_ntop.o
udpcli01.o: udpcli01.c echo.h 
dg_cli.o: dg_cli.c echo.h
sock_ntop.o: sock_ntop.c echo.h