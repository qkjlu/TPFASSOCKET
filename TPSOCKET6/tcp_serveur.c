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
#include <errno.h>

#define PORT 10000
#define NB_THREAD 500

char buffer[32];
int sock;

typedef struct {
  int *i;
  int sock;
  int csock;
  struct sockaddr_in sin;
  struct sockaddr_in csin;
  
} threads_args_struct;

void f(){
  shutdown(sock,2);
  /* Fermeture de la socket serveur */
  close(sock);
  kill(getpid(),SIGTERM);
}

void* threadAction(void *args){
  pthread_detach(pthread_self());
  threads_args_struct *actualArgs = args;
  printf("Un client se connecte avec la socket %d de %s:%d\n",
    actualArgs->sock, inet_ntoa(actualArgs->csin.sin_addr), htons(actualArgs->csin.sin_port));

  int *i = actualArgs->i;

  while( recv(actualArgs->csock,buffer,32,0) != 0){
    printf("%s\n",buffer);
  }
  
  (*i)--;
  
     
}


int main(void) {

  // Ensemble des threads plus numéro thread et erreur éventuelle à la création du thread
  pthread_t threads[NB_THREAD];
  int i = 0;
  int err;

  int sock;
  int csock;

  /* Socket et contexte d'adressage du serveur */
  struct sockaddr_in sin;
  
  socklen_t recsize = sizeof(sin);
    
  /* Socket et contexte d'adressage du client */
  struct sockaddr_in csin;
  
  socklen_t crecsize = sizeof(csin);
 
  /* Création d'une socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuration */
  sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
  sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
  sin.sin_port = htons(PORT);               /* Listage du port */
  bind(sock, (struct sockaddr*)&sin, recsize);

  /* Démarrage du listage (mode server) */
  while(listen(sock, 5) != 0){
    printf("Erreur au lancement de l'écoute - Code erreur : %s\n",strerror(errno));
    printf("Lancement d'une autre tentative dans 2 secondes\n");
    sleep(2);
  }

  /* Attente d'une connexion client */
  while (i < NB_THREAD){
    
    csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
    threads_args_struct *args = malloc(sizeof *args);
    args->sock = sock;
    args->csock = csock;
    args->sin = sin;
    args->csin = csin;
    args->i = &i;
    err = pthread_create(&(threads[i]), NULL, &threadAction, args);
    if (err != 0){
      printf("Erreur à la création du thread\n");
    }
    i++;
    signal(SIGINT,f);
        
  }

  return EXIT_SUCCESS;

}//main
