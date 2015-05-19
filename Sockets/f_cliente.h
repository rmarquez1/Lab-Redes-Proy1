#ifndef FUNCIONESC_H
#define FUNCIONESC_H

#include "funciones.h"

void printAvailbleSeats(char* buffer);
void manageResponse(char* echoString, int sock);
void convertSite(char* file, char* column, char* echoString);
int  verifyFile(int file);
int  verifyColumn(int column);
void getFile(char* buffer);
void getColumn(char* buffer);

#endif