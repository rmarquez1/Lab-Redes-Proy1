/**
 *@file: funciones.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez     10-10849
 *Proyecto 1: Programación con sockets/Protocolos de comunicacion
 */

#ifndef FUNCIONES_C
#define FUNCIONES_C

#include "funciones.h"

void DieWithError(char *errorMessage)
{
	perror (errorMessage);
	exit(1);
}


void DieThreadWithError(char *errorMessage)
{
	printf("%s\n", errorMessage);
	pthread_exit(NULL);
}
#endif