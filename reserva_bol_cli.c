/**
 *@file: reserva_bol_cli.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez	 10-10849
 *Proyecto 1: Programación con sockets/Protocolos de comunicacion
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "f_cliente.h"

/*
 * Programa Principal
 * @param argc:   Cantidad de argumentos de entrada.
 * @param argv[]: Arreglo que contiene los argumentos de entradas.
 */

int main(int argc, char *argv[])
{
	int sock; 
	struct sockaddr_in echoServAddr; 
	unsigned short echoServPort; 
	char *servIP;
	char echoString[RCVBUFSIZE]; 
	int file;
	int column;
 	int i;

 	if (argc<8){
 		perror("Error: Numero de argumentos invalidos.\n"
 			"	Introduzca: reserva_bol_cli <ip-servidor> -p <puerto servicio> -f <fila> -c <col>\n");
 		exit(1);
 	}

 	/* Verificamos los argumentos */
 	for (i=2; i<argc;i++){
 		if (strcmp("-p",argv[i])==0){
 			i++;
 			/* Verificamos que sea un numero entero */
 			if (!(echoServPort=atoi(argv[i])))
 				DieWithError("ERROR: EL VALOR SEGUIDO DE [-p] DEBE SER UN NUMERO ENTERO\n");

 		} else if(strcmp("-f",argv[i])==0){
 			i++;
 			/* Verificamos que sea un numero entero */
 			if (!(file=atoi(argv[i])))
 			 	DieWithError("ERROR: EL VALOR SEGUIDO DE [-f] DEBE SER UN NUMERO ENTERO\n");

 			if(verifyFile(file))
 				DieWithError("ERROR: EL RANGO DE VALORES PARA LA FILA ES DE [0,10)\n");

 		} else if(strcmp("-c",argv[i])==0){
 			i++;
  			if (!(column=atoi(argv[i])))
 				DieWithError("ERROR: EL VALOR SEGUIDO DE [-c] DEBE SER UN NUMERO ENTERO\n");

 			/* Verificamos que sea un numero entero */
 			if(verifyColumn(column))
 				DieWithError("ERROR: EL RANGO DE VALORES PARA LA COLUMNA ES DE [0,4)\n");

 		} else {
 			DieWithError("Error: Argumentos invalidos.\n"
 					"	Introduzca: reserva_bol_ser -f <filas> -c <col> [-p puerto]\n");
 		}
 	}

	servIP = argv[1];
	
	char fil[MAX_LENGTH];
	char col[MAX_LENGTH];

	sprintf(fil, "%d", file);
	sprintf(col, "%d", column);

	convertSite(fil, col, echoString);

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("La funcion socket en el archivo reserva_bol_cli fallo");

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(echoServPort);

	int attemps = 0;

	while (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
	{
		if(++attemps == MAX_ATTEMPTS)
			DieWithError("La funcion connect en el archivo reserva_bol_cli fallo");
		else
		{
			printf("%s\n", "Fallo el intento de conectar al servidor\nIntentando de nuevo en 5 segundos");	
			sleep(5);
		}
	}

	manageResponse(echoString, sock);
	
	close(sock);
	exit(0);
}