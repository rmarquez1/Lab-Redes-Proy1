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


#endif