/**
 *@file: f_servidor.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez     10-10849
 *Proyecto 1: Programación con sockets/Protocolos de comunicacion
 */

void die(char *message) {
  perror(message);
  exit(1);
}

void copyData(int from, int to) {
  char buf[1024];
  int amount;

 
  while ((amount = read(from, buf, sizeof(buf))) > 0){
    if (write(to, buf, amount) != amount) {
      die("write");
      return;
    }
  }
  
  if (amount < 0) die("read");



}

/**
 * crear_conexion:
 *  Se encarga de crear una conexion TCP/IP,  especificando el puerto
 *  por donde se realiza la comunicacion con los clientes devolviendo el
 * socket descriptor de la conexion
 *
 * @param puerto:  puerto por donde se realiza la comunicacion
 * @return sock: sock resultado de la conexion, para comunicarse
 */
int crear_conexion(int puerto){

    struct sockaddr_in address;
    struct sockaddr_in remote_address;
    int sock,conn;
    size_t addrLength = sizeof(struct sockaddr_in);

    /**
     * Abrimos el socket
     * AF_INET    :Protocolos de Internet IPv4
     * SOCK_STREAM:Tipo orientado a conexion 
     */
     if((sock = socket(AF_INET, SOCK_STREAM, 0))==-1){
        perror("Error: creacion socket servidor");
        exit(1);
     }

     address.sin_family = AF_INET;                          /**Es el tipo de conexión*/
     address.sin_port   = htons(puerto);                    /**Es el número correspondiente al servicio */
     address.sin_addr.s_addr = htons(INADDR_ANY);           /**IP local*/
    
     if((bind(sock, (struct sockaddr *)&address,sizeof(struct sockaddr)))==-1){
         perror("Error: bind\n");
     }

     if ((listen(sock, 100)) == -1){
        perror("Error: listen");
        exit(1);
     }
      while((conn = accept(sock, (struct sockaddr *) &address, &addrLength)) >= 0) {
        printf("...getting data\n");
                copyData(conn,1);
                printf("...Done\n");
                close(conn);
     }
	return sock;
}