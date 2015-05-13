/**
 *@file: f_cliente.c
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
 * conectar_servidor:
 * Se encarga de crear una conexion TCP/IP,  especificando el puerto
 * por donde se realiza la comunicacion con el servidor devolviendo el
 * socket descriptor de la conexion
 * Se crea ademas un hilo que atiende a la sala por default
 *
 * @param puerto:  puerto por donde se realiza la comunicacion
 * @return host_c: host para la conexion
 */
int conectar_servidor(char host_c[], int puerto){

    struct sockaddr_in address;
    struct in_addr inaddr;
    struct hostent *host;        /**Estructura del host*/
    int sock;

    if (inet_aton(host_c, &inaddr)){ /**IP*/
         host = gethostbyaddr((char *) &inaddr, sizeof(inaddr), AF_INET);
    } else {  /**DNS*/
         if((host=gethostbyname(host_c))==NULL){
             perror("Error: Error en la direccion HOST");
             exit(1);
         }
    }
     
    /**
     * Abrimos el socket
     * AF_INET    :Protocolos de Internet IPv4
     * SOCK_STREAM:Tipo orientado a conexion 
     */
     if((sock = socket(AF_INET, SOCK_STREAM, 0))==-1){
        perror("Error: Abriendo el socket");
        exit(1);
     }
     address.sin_family = AF_INET;                          /**Es el tipo de conexión*/
     address.sin_port   = htons(puerto);                    /**Es el número correspondiente al servicio */
     address.sin_addr = *((struct in_addr *)host->h_addr);
     address.sin_addr.s_addr = inet_addr("127.0.0.1");     /**Dirección de la máquina*/

     if((connect(sock,(struct sockaddr*)&address,sizeof(address))) == -1){ 
        perror("Error\n");
        exit(1);
     }

     /*
	if(send(sock,"Hola Servidor",TAMANO,0) == -1){
		perror("Error: send\n");
		exit(1);
	}*/
        copyData(0, sock);

      //close(sock);
     return sock;
}