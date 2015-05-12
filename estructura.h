/**
 *@file: estructura.h
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez	 10-10849
 *Proyecto 1: Programación con sockets/Protocolos de comunicacion
 */

#ifndef ESTRUCTURA_H_
#define ESTRUCTURA_H_

/***************
 *  Librerias  *
 ***************/
#define MAX_FILAS 10 	//Numero maximo de filas en un vagon
#define MAX_COLUMNAS 4  //Numero maximo de columanas en un vagon 
#define TAMANO 1024
#define TRUE   1
#define FALSE  0
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include "estructura.h"


/**
* Estructura de Clientes:
* @nombre: nombre del cliente en el  chat.
* @id_hilo: id del hilo que representa el cliente. 
* @socket: id del socket con el que la sala se comunica con el cliente
* @prox: apuntador al proximo en la lista de clientes asociados a la sala.
*/ 
struct asiento{
	int fila, col, ocupado;   
};

typedef struct asiento Asiento;
typedef struct asiento *ASIENTO;


Asiento asientos[MAX_FILAS][MAX_COLUMNAS];

extern int estaReservado(int fila, int col);
extern int vagonLleno();
extern int reservar(int fila, int col);

#endif /*ESTRUCTURA_H_*/