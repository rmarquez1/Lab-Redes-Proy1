/**
 *@file: estructura_server.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez     10-10849
 *Proyecto 1: RPC
 */

#include "estructura.h"

Asientos asientos[MAX_FILAS][MAX_COLUMNAS];

char *itoa (int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

/*
 * vagonLleno:
 * Verifica si todos los asientos estan ocupados. Retorna 1 en caso de que
 * este lleno y 0 en caso contrario
 */
int vagonLleno(){
	int i,j;
	for(i=0;i<MAX_FILAS;i++){
		for(j=0;j<MAX_COLUMNAS;j++){
			if (asientos[i][j].ocupado!=1) return FALSE;
		}
	}
	return TRUE;
}

/*
 * estaReservado:
 * Verifica que dado una fila y columna de asiento, este ya este reservado
 * Retorna 1 en caso de que este reservado y 0 en caso contrario
 */
int estaReservado(int fila, int col){
	if (asientos[fila-1][col-1].ocupado == 1) return TRUE;
	return FALSE;
}


/**
 * reservar_1_svc:
 * Se encarga de reservar un puesto en el vagon.
 * Retorna 0 en caso de que el vagon este lleno. 1 si esta ocupadp
 * Y 2 si se reserva.
 */
int *
reservar_1_svc(asiento *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */
	if (vagonLleno() == 1) result = 0;
	else{
		if (estaReservado(argp->fila,argp->col) == 1){
			result = 1;
		}
		else{
			asientos[argp->fila-1][argp->col-1].ocupado = 1;
			result = 2;
		}
	}
	return &result;
}


/**
 * esta_reservado_1_svc:
 * Indica si un puesto esta reservado o no.
 * Retorna 1 si esta reservado y 0 en caso contrario
 */
int *
esta_reservado_1_svc(asiento *argp, struct svc_req *rqstp)
{
	static int  result;
	 
	result = estaReservado(argp->fila,argp->col);
	return &result;
}

