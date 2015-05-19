#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <time.h>

#define RCVBUFSIZE 64
#define MAX_FILES 10	//Numero maximo de filas en un vagon
#define MAX_COLUMNS 4  //Numero maximo de columanas en un vagon 
#define MAX_LENGTH 10
#define MAX_ATTEMPTS 3
#define STRING_EXIT "exit"
#define MAXPENDING 5

void DieWithError(char *errorMessage);
void DieThreadWithError(char *errorMessage);
char* getTime ();
char* getClientIP(struct sockaddr_in echoClntAddr);
void DieWithError(char *errorMessage);

#endif