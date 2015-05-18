/**
 *@file: reserva_bol_ser.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez	 10-10849
 *Proyecto 1: Programación con sockets/Protocolos de comunicacion
 */

 #include "f_servidor.h"

/*
 * Programa Principal
 * @param argc:   Cantidad de argumentos de entrada.
 * @param argv[]: Arreglo que contiene los argumentos de entradas.
 */
int main(int argc, char *argv[])
{
	int servSock;
	int clntSock;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClntAddr;
	unsigned short echoServPort;
	unsigned int clntLen;
	pthread_t clientThread;

 	if (argc<7 || argc>7){
 		perror("Error: Numero de argumentos invalidos.\n"
 			"	Introduzca: reserva_bol_ser -f <filas> -c <col> [-p puerto]");
 		exit(1);
 	}
 	/* Verificamos los argumentos */
 	int i;

 	for (i=1; i<argc;i++){
 		if (strcmp("-f",argv[i])==0){
 			i++;
 			/* Verificamos que sea un numero entero */
 			if (!(atoi(argv[i]))){
 				DieWithError("ERROR: EL VALOR SEGUIDO DE [-f] DEBE SER UN NUMERO ENTERO");
 			}
 		}else if(strcmp("-c",argv[i])==0){
 			i++;
 			/* Verificamos que sea un numero entero */
 			if (!(atoi(argv[i]))){
 				DieWithError("ERROR: EL VALOR SEGUIDO DE [-c] DEBE SER UN NUMERO ENTERO");
 			}
 		}else if(strcmp("-p",argv[i])==0){
 			i++;
 			/* Verificamos que sea un numero entero */
 			if (!(atoi(argv[i]))){
 				DieWithError("ERROR: EL VALOR SEGUIDO DE [-p] DEBE SER UN NUMERO DE PUERTO");
 			}
 		}else{
 			DieWithError("Error: Argumentos invalidos.\n"
 					"	Introduzca: reserva_bol_ser -f <filas> -c <col> [-p puerto]");
 		}
 	}

	echoServPort = atoi(argv[6]);

	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError( "La funcion socket en el archivo reserva_bol_ser.c fallo") ;

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	echoServAddr.sin_port = htons(echoServPort);

	if (bind(servSock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
		DieWithError ("La funcion bind en el archivo reserva_bol_ser.c fallo");

	if (listen(servSock, MAXPENDING) < 0)
		DieWithError("La funcion listen en el archivo reserva_bol_ser.c fallo");

	initializeTrain();

	for(;;)
	{
		clntLen = sizeof(echoClntAddr);

		if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
			DieWithError("La funcion accept en el archivo reserva_bol_ser.c fallo");

   		if((pthread_create(&clientThread,NULL,HandleTCPClient,(void*)&clntSock)) != 0)
        	DieWithError("fallo la creacion del hilo en el archivo reserva_bol_ser"); 
	}
}
