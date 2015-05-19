/* estructura.x */


const MAX_FILAS = 10;
const MAX_COLUMNAS = 4;
const TAMANO = 1024;
const TRUE = 1;
const FALSE = 0;

struct asiento{
	int fila;
	int col;
};

struct Asientos{
	int fila;
	int col;
	int ocupado;
};

program RESERVA_BOLETOS{
	version RESERVA_BOLETOS_VERS{
		int reservar(asiento) =1;
		int esta_reservado(asiento)=2;
	} = 1;
} = 0x30090948;