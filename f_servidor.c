/**
 *@file: f_servidor.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez     10-10849
 *Proyecto 1: Programación con sockets/Protocolos de comunicacion
 */

#ifndef FUNCIONESS_C
#define FUNCIONESS_C

#include "f_servidor.h"

//Variable que representa el estado del tren
Train globlalTrain;

//Semaforo para asegurarnos que dos hilos que atienden clientes no se interpongan mientras acceden a la variable globlalTrain
pthread_mutex_t lockTrain = PTHREAD_MUTEX_INITIALIZER;


/**
 * initializeTrain:
 * Se encarga de inicializar el tren con todos los asientos vacios
 */
void initializeTrain()
{
	int i = 0;
	int j = 0;

	while(i < MAX_FILES)
	{
		j = 0;
		while(j < MAX_COLUMNS)
		{
			globlalTrain.seats[i][j++] = 0;
		}
		i++;
	}
	globlalTrain.cantOccupied = 0;
}

/**
 * trainToString:
 * Se encargada de convertir el estado del tren en un string para ser enviado al cliente en caso de
 * que este haya pedido un asiento ocupado y se deba retornar la lista de asientos ocupados
 * @param buffer:  string en el que se escribira el estado del tren
 */
void trainToString(char* buffer)
{
	int i = 0;
	int j = 0;
	char auxBuffer[2];
	
	pthread_mutex_lock(&lockTrain);

	while(i < MAX_FILES)
	{
		j = 0;
		while(j < MAX_COLUMNS)
		{
			sprintf(auxBuffer, "%d", globlalTrain.seats[i][j++]);
			strcat(buffer, auxBuffer);
		}
		i++;
	}

	pthread_mutex_unlock(&lockTrain);

}

/**
 * verifySeat:
 * Se encarga de verificar que el asiento representado por las variables file y column
 * se encuentra disponible o ocupado. En caso que el asiento esta ocupado retorna 1, en
 * en caso que este disponible retorna 0 y en caso que el vagon este lleno retorna 2.
 * @param file:  fila del asiento
 * @param column:  columna del asiento
 * @return r: estado del asiento
 */
int verifySeat(int file, int column)
{
	int r;
	pthread_mutex_lock(&lockTrain);
	if(globlalTrain.cantOccupied == MAX_COLUMNS * MAX_FILES)
		r = 2;
	else
		if(globlalTrain.seats[file][column] == 1)
			r = 1;
		else
		{
			globlalTrain.seats[file][column] = 1;
			globlalTrain.cantOccupied++;
			r = 0;
		}
	pthread_mutex_unlock(&lockTrain);
	return r;
}

/**
 * HandleTCPClient:
 * Se encarga de manejar todo el proceso de comunicacion con el cliente
 * @param sock:  socket por el que se realiza la comunicacion
 */
void* HandleTCPClient(void* sock)
{
	int clntSocket = *(int*) sock; 
	char echoBuffer[RCVBUFSIZE];
	int recvMsgSize;

	if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE-1, 0)) < 0)
		DieThreadWithError("recv() failed");

	echoBuffer[recvMsgSize] = '\0';

	printf("%s\n", echoBuffer);

	if(strcmp(echoBuffer, STRING_EXIT) == 0)
		DieThreadWithError("El cliente decidio cerrar la conexion");
	
	int f = getNumber(echoBuffer, 'F', 'C');
	int c = getNumber(echoBuffer, 'C', '\0');
	int r = verifySeat(f,c);

	sprintf(echoBuffer, "%d", r);

	if(r == 0) 		  strcat(echoBuffer, "\n");
	else if(r == 1) { strcat(echoBuffer, "\n"); trainToString(echoBuffer);  strcat(echoBuffer, "\n"); }
	else if(r == 2)   strcat(echoBuffer, "\n");
	else DieThreadWithError("Ocurrio un error inesperado del lado del servidor");

	unsigned int strBufferLen = strlen(echoBuffer);
	
	if (send(clntSocket, echoBuffer, strBufferLen, 0) != strBufferLen)
			DieThreadWithError("send() failed");

	if(r == 1)
		HandleTCPClient(sock);

	close(clntSocket);
	pthread_exit(NULL);
}

/**
 * getNumber:
 * Funcion ancargada de separar un string a partir del caracter begin
 * hasta el caracter end y convertir el resultado a un entero
 * @param cMessage:  string que se desea separar
 * @param begin:  caracter que representa el comienzo del entero
 * @param end:  caracter que representa el fin del entero
 * @return cnvtBuffer: entero que deseamos extraer
 */
int getNumber(char* cMessage, char begin, char end)
{
	char cnvtBuffer[RCVBUFSIZE];

	while((*cMessage) != begin) cMessage++;

	int i = 0;
	cMessage++;

	while((*cMessage) != end) 
	{ 
		cnvtBuffer[i++] = *cMessage; 
		cMessage++; 
	}
	
	cnvtBuffer[i] = '\0';

	return(atoi(cnvtBuffer));
}
#endif
