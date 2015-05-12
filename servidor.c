/**
 *@file: servidor.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez	 10-10849
 *Proyecto 1: Programación con sockets/Protocolos de comunicacion
 */

 #include "estructura.h"

/*
 * Programa Principal
 * @param argc:   Cantidad de argumentos de entrada.
 * @param argv[]: Arreglo que contiene los argumentos de entradas.
 */
 int main(int argc, char *argv[]){

 	int flag;
 	int fila;
 	int col;
 	int puerto;
 	int i;
 	int socketServidor;

 	if (argc<5 || argc>7){
 		perror("Error: Numero de argumentos invalidos.\n"
 			"	Introduzca: reserva_bol_ser -f <filas> -c <col> [-p puerto]");
 		exit(1);
 	}

 	/* Verificamos los argumentos */
 	for (i=0; i<argc;i++){
 		if (strcmp("-f",argv[i])==0){
 			i++;
 			/* Verificamos que sea un numero entero */
 			if (!(fila=atoi(argv[i]))){
 				printf("ERROR: EL VALOR SEGUIDO DE [-f] DEBE SER UN NUMERO ENTERO");
 				exit(1);
 			}
 		}else if(strcmp("-c",argv[i])==0){
 			i++;
 			/* Verificamos que sea un numero entero */
 			if (!(col=atoi(argv[i]))){
 				printf("ERROR: EL VALOR SEGUIDO DE [-c] DEBE SER UN NUMERO ENTERO");
 				exit(1);
 			}
 		}else if(strcmp("-p",argv[i])==0){
 			i++;
 			/* Verificamos que sea un numero entero */
 			if (!(puerto=atoi(argv[i]))){
 				printf("ERROR: EL VALOR SEGUIDO DE [-c] DEBE SER UN NUMERO DE PUERTO");
 				exit(1);
 			}
 		}else{
 			perror("Error: Argumentos invalidos.\n"
 					"	Introduzca: reserva_bol_ser -f <filas> -c <col> [-p puerto]");
 		}
 	}

 	return 0;
 }