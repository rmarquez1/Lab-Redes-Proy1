/**
 *@file: f_cliente.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez     10-10849
 *Proyecto 1: Programación con sockets/Protocolos de comunicacion
 */

#ifndef FUNCIONESC_C
#define FUNCIONESC_C

#include "f_cliente.h"

/**
 * verifyFile:
 * Se encarga de verificar que un numero entero esta en el rango [0..MAX_FILES)
 * Esto para verificar que no se intenta reservar un asiento fuera de rango
 * @param file:  numero que se desea verificar
 * @return bool: Si el numero esta en el rango
 */

int verifyFile(int file)
{
	return ((file < 0) || (file > MAX_FILES - 1));
}

/**
 * verifyColumn:
 * Se encarga de verificar que un numero entero esta en el rango [0..MAX_COLUMNS)
 * Esto para verificar que no se intenta reservar un asiento fuera de rango
 * @param column:  numero que se desea verificar
 * @return bool: Si el numero esta en el rango
 */

int verifyColumn(int column)
{
	return ((column < 0) || (column> MAX_COLUMNS - 1));
}

/**
 * convertSite:
 * Se encarga de recibir una fila, una columna y los convierte al formato
 * de comunicacion entre cliente y el servidor para reservar un asiento
 * el formato es F<fila>C<columna>\0. 
 * @param file:  string que representa una fila
 * @param column:  string que representa una columna
 * @return echoString: Buffer
 */
void convertSite(char* file, char* column, char* echoString)
{
    strcpy(echoString, "F");
	strcat(echoString, file);
	strcat(echoString, "C");
	strcat(echoString, column);
	strcat(echoString, "\0");
}

/**
 * manageResponse:
 * Se encarga de manejar todo el proceso de comunicacion con el servidor.
 * Envia el mensaje almacenado en la varible echoString a traves del socket sock
 * Dependiendo de la respuesta imprime por pantalla si el vagon esta lleno, si la reserva
 * se hizo correctamente o, en caso de que el asiento estuvera ocupado, pide una fila y columna nuevos.
 * @param echoString:  mensaje que desea ser enviado
 * @param sock:  socket por el que deseamos comunicarnos
 */
void manageResponse(char* echoString, int sock)
{
	unsigned int echoStringLen = strlen(echoString);
	int bytesRcvd; 
	char echoBuffer[RCVBUFSIZE]; 

	if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
		DieWithError("Error en la funcion send, se envio un numero distinto de bytes del esperado");

	if(strcmp(echoString, STRING_EXIT) != 0)
	{	
		if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
			DieWithError("Error en la funcion recv, fallo la conecion o se cerro premturamente");

		echoBuffer[bytesRcvd] = '\0';
		int r = atoi(echoBuffer);

		if(r == 0) 		printf("%s\n", "La reserva se realizo correctamente");
		else if(r == 1) 
		{ 
			printf("%s\n", "La reserva no pudo ser realizada porque el asiento no esta disponible"); 
	    	printf("%s\n", "Por favor, seleccione uno disponible de la siguiente lista");
	    	printf("%s\n", "(0 = disponible, 1 = ocupado, exit = salir)");
	    	printAvailbleSeats(echoBuffer);
	    	
	    	char fil[MAX_LENGTH];
	    	char col[MAX_LENGTH];

	    	getFile(fil);
	    	getColumn(col);

	    	if((strcmp(fil, STRING_EXIT) == 0))
	    	{
	    		manageResponse(STRING_EXIT, sock);
	    	} else
	    	{
	    		convertSite(fil, col, echoBuffer);
				manageResponse(echoBuffer, sock);
		    }
	    }
		else if(r == 2) printf("%s\n", "El tren esta lleno");
	}
}

/**
 * getFile:
 * Se encarga de pedir un numero por entrada estandar y asegurarse que esta
 * en el rango [0..MAX_FILES). Lo escribe en la variable buffer
 * @param buffer:  variable en la que escribir la entrada
 */
void getFile(char* buffer)
{
	printf("%s\n", "Fila: ");
	scanf("%s", buffer);

	if(strcmp(buffer, STRING_EXIT) == 0) return;

	while(verifyFile(atoi(buffer)))
	{
		printf("%s\n", "El valor de la fila esta afuera del rango [0..9)");
		printf("%s\n", "Fila: ");
		scanf("%s", buffer);
		if(strcmp(buffer, STRING_EXIT) == 0) return;
	};
}

/**
 * getColumn:
 * Se encarga de pedir un numero por entrada estandar y asegurarse que esta
 * en el rango [0..MAX_COLUMNS). Lo escribe en la variable buffer
 * @param buffer:  variable en la que escribir la entrada
 */
void getColumn(char* buffer)
{
	printf("%s\n", "Columna ");
	scanf("%s", buffer);
	if(strcmp(buffer, STRING_EXIT) == 0) return;
	while(verifyColumn(atoi(buffer)))
	{ 
		printf("%s\n", "El valor de la columna esta afuera del rango [0..4)");
		printf("%s\n", "Columna ");
		scanf("%s", buffer);
		if(strcmp(buffer, STRING_EXIT) == 0) return;
	};
}

/**
 * printAvailbleSeats:
 * Se encarga de imprimir de manera ordenada la lista de asientos representada en el string buffer
 * @param buffer:  variable que almacena la lista de asientos
 */
void printAvailbleSeats(char* buffer)
{
	int i = 0;
	int j = 0;

	while((*buffer) != '\n') buffer++;	
	buffer++;

	printf("%s", "      C0 C1 C2 C3");
	while(i < MAX_FILES*MAX_COLUMNS)
	{
		if(i % MAX_COLUMNS == 0)
			printf("\nF%d -> ", j++);

		printf("%c  ", buffer[i]);
		i++;
	}
	printf("\n");
}

#endif