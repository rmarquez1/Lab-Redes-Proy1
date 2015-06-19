CC = gcc
CFLAGS = -g -lpthread

all : reserva_bol_ser reserva_bol_cli

funciones.o : funciones.c funciones.h
	$(CC) $(CFLAGS) -c funciones.c

f_cliente.o : f_cliente.c f_cliente.h
	$(CC) $(CFLAGS) -c f_cliente.c

f_servidor.o : f_servidor.c f_servidor.h
	$(CC) $(CFLAGS) -c f_servidor.c

reserva_bol_ser : reserva_bol_ser.c funciones.o f_servidor.o
	$(CC) $(CFLAGS) reserva_bol_ser.c funciones.o f_servidor.o -o reserva_bol_ser 

reserva_bol_cli : reserva_bol_cli.c funciones.o f_cliente.o
	$(CC) $(CFLAGS) reserva_bol_cli.c funciones.o f_cliente.o -o reserva_bol_cli 

clean:
	rm *.o reserva_bol_cli reserva_bol_ser
