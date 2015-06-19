/**
 *@file: estructuras_svc.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez     10-10849
 *Proyecto 1: RPC
 */

#include "estructura.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
reserva_boletos_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		asiento reservar_1_arg;
		asiento esta_reservado_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case reservar:
		_xdr_argument = (xdrproc_t) xdr_asiento;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) reservar_1_svc;
		break;

	case esta_reservado:
		_xdr_argument = (xdrproc_t) xdr_asiento;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) esta_reservado_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (RESERVA_BOLETOS, RESERVA_BOLETOS_VERS);
	int fila,col,i;
	
	if (argc<5){
 		perror("Error: Numero de argumentos invalidos.\n"
 			"	Introduzca: ./reserva_bol_ser -f <fila> -c <col>\n");
 		exit(1);
 	}

 	/* Verificamos los argumentos */
 	for (i=1; i<argc;i++){
 		if (((i!=1) && (strcmp("-f",argv[i])==0)) || ((i!=3) && (strcmp("-c",argv[i])==0))) {
 			perror("Orden en los argumentos invalido.\n"
 					"	Introduzca: ./reserva_bol_ser -f <fila> -c <col>\n");
 			exit(1);
 		}else if (((i==1) && (strcmp("-f",argv[i])!=0)) || ((i==3) && (strcmp("-c",argv[i])!=0))) {
 			perror("Orden en los argumentos invalido.\n"
 					"	Introduzca: ./reserva_bol_ser -f <fila> -c <col>\n");
 			exit(1);
 		}
 	}

 	for (i=1; i<argc;i++){
 		if (strcmp("-f",argv[i])==0){
 			i++;
 			/* Verificamos que sea un numero entero */
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
 			/* Verificamos que sea un numero entero */
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
 					"	Introduzca: ./reserva_bol_ser -f <fila> -c <col>\n");
 			exit(1);
 		}
 	}

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, RESERVA_BOLETOS, RESERVA_BOLETOS_VERS, reserva_boletos_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (RESERVA_BOLETOS, RESERVA_BOLETOS_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, RESERVA_BOLETOS, RESERVA_BOLETOS_VERS, reserva_boletos_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (RESERVA_BOLETOS, RESERVA_BOLETOS_VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
