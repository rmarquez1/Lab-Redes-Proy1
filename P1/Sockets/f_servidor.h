#ifndef FUNCIONESS_H
#define FUNCIONESS_H

#include "funciones.h"

typedef struct train
{
	int seats[MAX_FILES][MAX_COLUMNS];
	int cantOccupied;
} Train;

void initializeTrain();
void trainToString(char* buffer);
int verifySeat(int file, int column);
void* HandleTCPClient(void* sock);
int getNumber(char* cMessage, char begin, char end);
void writeLog(char* message);
void writeFromClientLog (struct sockaddr_in echoClntAddr, int clntSock);
void writeRecvLog(char* echoBuffer, int clntSocket);
void writeLogCloseClient(int clntSocket);
void writeLogSend(int clntSocket, char* echoBuffer);

#endif