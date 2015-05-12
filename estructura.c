/**
 *@file: estructura.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez	 10-10849
 *Proyecto 1: Programación con sockets/Protocolos de comunicacion
 */
#include "estructura.h"

/*
 * estaReservado:
 * Verifica que dado una fila y columna de asiento, este ya este reservado
 * Retorna 1 en caso de que este reserado y 0 en caso contrario
 */
int estaReservado(int fila, int col){
	if (asientos[fila][col].ocupado == 1) return TRUE;
	return FALSE;
}

/*
 * vagonLleno:
 * Verifica si todos los asientos estan ocupados. Retorna 1 en caso de que
 * este lleno y 0 en caso contrario
 */
int vagonLleno(){
	for(int i=0;i<MAX_FILAS;i++){
		for(int j=0;j<MAX_COLUMNAS;j++){
			if (asientos[i][j].ocupado==0) return FALSE;
		}
	}
	return TRUE;
}

/*
 * reservar:
 * Reserva un asiento dado la fila y la columna a la que pertenece
 * @return 0: cuando el vagon esta lleno
 * @return 1: cuando el asiento ya ha sido reservado
 * @return 2: cuando se realiza la reserva son  problemas. 
 */
int reservar(int fila, int col){
	if (vagonLleno() == 1) return 0;
	else{
		if (estaReservado(fila,col) == 1) return 1;
		else{
			asientos[fila][col].ocupado = 1;
			return 2;
		}
	}
}