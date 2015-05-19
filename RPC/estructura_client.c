/**
 *@file: estructura_client.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez     10-10849
 *Proyecto 1: RPC
 */

#include "estructura.h"

void
reserva_boletos_1(char *host, int fila, int col)
{
	CLIENT *clnt;
	int  *result_1;
	asiento  reservar_1_arg;
	int  *result_2;
	asiento  esta_reservado_1_arg;
	int f,c;
	int intentos;
	intentos = 0;
	int i,j;

#ifndef	DEBUG
	clnt = clnt_create (host, RESERVA_BOLETOS, RESERVA_BOLETOS_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	while(TRUE){
		// Este es el primer intento cuando escribimos la primera llamada
		if (intentos == 0){
			reservar_1_arg.fila = fila;
			reservar_1_arg.col = col;
			result_1 = reservar_1(&reservar_1_arg, clnt);
		}else{ // Cuando el asiento que solicito esta ocupado y vuelve a intentar
			while (TRUE){
				printf("Inserte fila: ");
				scanf("%d",&f);
				if (f<1 || f>10){
					printf("********* Error: El rango de valores para la fila es de [1,10]. Intentelo de nuevo...\n");
				}else break;
			}
			while (TRUE){
				printf("Inserte columna: ");
				scanf("%d",&c);
				if (c<1 || c>4){
					printf("********* Error: El rango de valores para la columna es de [1,4]. Intentelo de nuevo...\n");
				}else break;
			}
			
			
			printf("\n");
			reservar_1_arg.fila = f;
			reservar_1_arg.col = c;
			result_1 = reservar_1(&reservar_1_arg, clnt);
		}

		if (result_1 == (int *) NULL) {
			clnt_perror (clnt, "call failed");
		}

		// Caso en que se puede reservar el asiento sin problemas
		if (*result_1 == 2){
			printf("¡Reservado!\n");
			exit(1);
		}else if (*result_1 == 1){ // Caso en que el asiento esta ocupado
			intentos++;
			if (intentos == 3){
				printf("¡Numero de intentos maximo agotado!\n");
        		exit(1);
        	}else{
        		printf("¡Ocupado!\n");
				printf("Los siguientes asientos estan disponibles:\n");
				printf("%s", "      C1 C2 C3 C4");
				int numfila;
				numfila=1;
        		for (i=1; i<=MAX_FILAS; i++){
			        esta_reservado_1_arg.fila = i;
			        printf("\nF%d -> ", numfila++);
			        for (j=1; j<=MAX_COLUMNAS; j++){
			        	esta_reservado_1_arg.col = j;
			            result_2 = esta_reservado_1(&esta_reservado_1_arg, clnt);
						if (result_2 == (int *) NULL) {
							clnt_perror (clnt, "call failed");
						}

						if(*result_2 == FALSE){
							printf("%d  ",0);
						}else printf("%d  ",1);
	        		}
    			}
    			printf("\n");

        	}
		}else {
			printf("¡Vagon completo!\n");
			exit(1);
		}
		
	}
	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	int flag;
 	int fila;
 	int col;
 	int puerto;
 	int i;
 	int socketCliente;
 	char linea[TAMANO];
 	//i = 4;
 
 	if (argc<6){
 		perror("Error: Numero de argumentos invalidos.\n"
 			"	Introduzca: ./reserva_bol_cli <ip-servidor> -f <fila> -c <col>\n");
 		exit(1);
 	}

	/* Verificamos los argumentos */
	for (i=2; i<argc;i++){
 		if (((i!=2) && (strcmp("-f",argv[i])==0)) || ((i!=4) && (strcmp("-c",argv[i])==0))) {
 			perror("Orden en los argumentos invalido.\n"
 					"	Introduzca: ./reserva_bol_cli <ip-servidor> -f <fila> -c <col>\n");
 			exit(1);
 		}else if (((i==2) && (strcmp("-f",argv[i])!=0)) || ((i==4) && (strcmp("-c",argv[i])!=0))) {
 			perror("Orden en los argumentos invalido.\n"
 					"	Introduzca: ./reserva_bol_cli <ip-servidor> -f <fila> -c <col>\n");
 			exit(1);
 		}
 	}


 	for (i=2; i<argc;i++){
 		if (strcmp("-f",argv[i])==0){
 			i++;

 			if (!(fila=atoi(argv[i]))){
 				perror("ERROR: EL VALOR SEGUIDO DE [-f] DEBE SER UN NUMERO ENTERO\n");
 				exit(1);
 			}
 			if ((fila<1) || (fila>10) ){
 				perror("ERROR: EL RANGO DE VALORES PARA LA FILA ES DE [1,10]\n");
 				exit(1);
 			}
 		}else if(strcmp("-c",argv[i])==0){
 			i++;
 			if (!(col=atoi(argv[i]))){
 				perror("ERROR: EL VALOR SEGUIDO DE [-c] DEBE SER UN NUMERO ENTERO\n");
 				exit(1);
 			}
 			if ((col<1) || (col>4) ){
 				perror("ERROR: EL RANGO DE VALORES PARA LA COLUMNA ES DE [1,4]\n");
 				exit(1);
 			}
 		}else{
 			perror("Error: Argumentos invalidos.\n"
 					"	Introduzca: ./reserva_bol_cli <ip-servidor> -f <fila> -c <col>\n");
 			exit(1);
 		}
 	}
	host = argv[1];
	reserva_boletos_1 (host, fila, col);
	exit (0);
}
