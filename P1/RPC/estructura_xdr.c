/**
 *@file: estructura_xdr
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez     10-10849
 *Proyecto 1: RPC
 */

#include "estructura.h"

bool_t
xdr_asiento (XDR *xdrs, asiento *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->fila))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->col))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Asientos (XDR *xdrs, Asientos *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->fila))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->col))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->ocupado))
		 return FALSE;
	return TRUE;
}
