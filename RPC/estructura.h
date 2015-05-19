/**
 *@file: estructura.h
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez     10-10849
 *Proyecto 1: RPC
 */

#ifndef _ESTRUCTURA_H_RPCGEN
#define _ESTRUCTURA_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAX_FILAS 10
#define MAX_COLUMNAS 4
#define TAMANO 1024


struct asiento {
	int fila;
	int col;
};
typedef struct asiento asiento;

struct Asientos {
	int fila;
	int col;
	int ocupado;
};
typedef struct Asientos Asientos;

#define RESERVA_BOLETOS 0x30090948
#define RESERVA_BOLETOS_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define reservar 1
extern  int * reservar_1(asiento *, CLIENT *);
extern  int * reservar_1_svc(asiento *, struct svc_req *);
#define esta_reservado 2
extern  int * esta_reservado_1(asiento *, CLIENT *);
extern  int * esta_reservado_1_svc(asiento *, struct svc_req *);
extern int reserva_boletos_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define reservar 1
extern  int * reservar_1();
extern  int * reservar_1_svc();
#define esta_reservado 2
extern  int * esta_reservado_1();
extern  int * esta_reservado_1_svc();
extern int reserva_boletos_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_asiento (XDR *, asiento*);
extern  bool_t xdr_Asientos (XDR *, Asientos*);

#else /* K&R C */
extern bool_t xdr_asiento ();
extern bool_t xdr_Asientos ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_ESTRUCTURA_H_RPCGEN */
