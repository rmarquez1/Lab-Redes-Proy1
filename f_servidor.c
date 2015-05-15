/**
 *@file: f_servidor.c
 *@Trimestre: Abril-Julio 2015
 *@Curso: Redes I CI-4815
 *@seccion: 1
 *@author: José Luis Jiménez 10-10839
 *@author: Ramón Márquez     10-10849
 *Proyecto 1: Programación con sockets/Protocolos de comunicacion
 */

#include "estructura.h"

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

pthread_t hilos_clientes[TAMANO];
pthread_t hilo_cliente;
pthread_mutex_t mutex_clientes[TAMANO];
pthread_mutex_t mutex_cliente;

/**
 * atender:
 *  Se encarga de atender a un cliente/usuario . Almacena los datos
 * enviados y procede a ejecutar los comandos dependiendo del caso
 *
 * @param sala: corresponde al identificador de la sala(chat) a enviar mensaje
 * @param socket: corresponde al identificador de la conexion
 */
void* atender( void* sock){

    int  tipo_comando;
    int  tam;                              //tamano de la estructra desconocida
    int socket;
    char usuario[TAMANO];// para nombre del usuario
    char comando[TAMANO];
    char mensaje[TAMANO];
    socket = *(int *)sock;
    /*
        printf("...getting data\n");
                copyData(socket,1);
                printf("...Done\n");
                close(socket);
   */
    while (TRUE){
        if(tam = recv (socket,&comando,TAMANO,0)== -1){
            printf("Error : No se pudo leer usuario en el socket servidor - cliente ");
             exit(1);
         }else{
            printf("%s\n",comando );
         }
    }
}


/**
 * trabajar_ servidor:
 * Corresponde a la sala/servidor creada al iniciar la ejecucion de schat. A esta sala le 
 * corresponde atender a todos los clientes que se conectan por primera vez y ademas
 * mantener un registro de estos que luego podran cambiar de sala.
 *
 * @param socket: corresponde al identificador de la conexion
 */
void*  trabajar_servidor(void* sock ){

    struct sockaddr_in address;
    struct sockaddr_in remote_address;
    int new_sock;
    int acceptados;
    int addrLength = sizeof(struct sockaddr );
    // Sala* sala = (Sala*)sal;     //CONVERSION A SALA
    int socket = *(int *) sock;   
    int i;
    int clientes;
    clientes = 0;
    //Para cada cliente que quiera conectarse, lo atiendo
    while(TRUE){
        new_sock = accept(socket,(struct sockaddr *) &address, &addrLength);
        if (new_sock < 0) {
            perror("ERROR en accept");
            exit(1);
        }
        
        if((pthread_create(&hilos_clientes[clientes],NULL,atender,(void*)&new_sock))!=0){ 
            perror("ERROR: creacion hilo cliente"); 
            exit(1);
        }
        clientes++;
        //atender(0,new_sock);  //Atender en sala por default
        
    }// cierre del while
    
    while (i<clientes){
        pthread_join(hilos_clientes[i],NULL);
    }
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
    int sock;
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
    return sock;
}

/**
 * conectar_cliente:
 *  Se encarga de crear una conexion TCP/IP,  especificando el puerto
 *  por donde se realiza la comunicacion con el servidor devolviendo el
 * socket descriptor de la conexion
 * Se crea ademas un hilo que atiende a la sala por default
 *
 * @param puerto:  puerto por donde se realiza la comunicacion
 * @return sock: sock resultado de la conexion, para comunicarse
 */
int conectar_cliente(int puerto){

   int sock;

   
   pthread_mutex_init(&mutex_cliente,NULL);

   sock = crear_conexion(puerto);

   if((pthread_create(&hilo_cliente,NULL,trabajar_servidor,(void*)&sock))!=0){ 
        perror("ERROR: creacion hilo clientes"); 
         exit(1);
    }
    pthread_join(hilo_cliente,NULL);
 
   
   return sock; /*retorno para cerrar*/
}

