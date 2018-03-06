// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#define PORT 10000
#define NB_THREAD 500

pthread_t threads[NB_THREAD];

void* threadAction(*void arg){
  printf("Un client se connecte avec la socket %d de %s:%d\n",
    sock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
     while(1){
       recv(csock,buffer,32,0);
       printf("%s\n",buffer);

     }
     pthread_detach();
     
}


int main(void) {

  // Numéro thread et erreur éventuelle à la création du thread
  int i = 0;
  int err;

  /* Socket et contexte d'adressage du serveur */
  struct sockaddr_in sin;
  int sock;
  socklen_t recsize = sizeof(sin);
    
  /* Socket et contexte d'adressage du client */
  struct sockaddr_in csin;
  int csock;
  socklen_t crecsize = sizeof(csin);
 
  /* Création d'une socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuration */
  sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
  sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
  sin.sin_port = htons(PORT);               /* Listage du port */
  bind(sock, (struct sockaddr*)&sin, recsize);

  /* Démarrage du listage (mode server) */
  listen(sock, 5);

  /* Attente d'une connexion client */
  while (i < NB_THREAD){
    char buffer[32] = "";
    csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
    err = pthread_create(&(threads[i]), NULL, &threadAction, NULL);
        
  }

  /* Fermeture de la socket client et de la socket serveur */
  close(csock);
  close(sock);
  return EXIT_SUCCESS;

}//main
