-- Integrantes
	Ramón Marquez 		10-10849
	José Luis Jiménez 	10-10839

-- Archivos
	-- reserva_bol_cli.c: Contiene todas la función principal que controla a los clientes.
	-- reserva_bol_ser.c: Contiene la función principal que controla al servidor.
	-- f_cliente.c: Contiene las funciones usadas por los clientes.
	-- f_servidor.c: Contiene las funciones usadas por el servidor.
	-- funciones.c: Contiene funciones generales y definiciones globales usadas por todo el resto de los archivos.
	-- Makefile.
	-- bitacora.txt: Archivo de texto en el que se guardan las acciones del servidor.

-- Ejecución del servidor
	./reserva_bol_ser -f <filas> -c <columna> -p <puerto>

-- Ejecución del cliente
	./reserva_bol_cli <ip-servidor> -p <puerto> -f <fila> -c <cliente>

-- Condiciones particulares
	-- Tanto la computadora que ejecuta al servidor como la que ejecuta al cliente debe tener una conexión activa a internet.
	-- Todos los números de entrada no deben exceder el número entero máximo representable en la máquina que se ejecutan. En
	   el caso de una máquina de 32 bits sería 2147483647 y en caso de 64 bits 4294967294.
	-- El puerto que usa el servidor por defecto es el 5555.  