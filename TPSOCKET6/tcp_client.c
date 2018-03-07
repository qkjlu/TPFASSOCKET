// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>

#define PORT 10000

int sock;

void f(){
  shutdown(sock,2);
  /* Fermeture de la socket client */
  close(sock);
  kill(getpid(),SIGTERM);
}

int main(void) {

  //int sock;
  struct sockaddr_in sin;

  /* Création de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);
 
  
 
  /* Configuration de la connexion */
  sin.sin_addr.s_addr = inet_addr("127.0.0.1");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
 
  /* Tentative de connexion au serveur */
  while(connect(sock, (struct sockaddr*)&sin, sizeof(sin)) != 0){
    
    printf("La connection a échoué - Code erreur : %s\n",strerror(errno));
    printf("Lancement d'une autre tentative dans 2 secondes\n");
    sleep(2);
  }
  
  printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr),
         htons(sin.sin_port));
  char buffer[32];
  char *pos;
  while(1) {
    printf("Entrer la chaine de caractère à envoyer au serveur \n");
    fgets(buffer,32,stdin);
    //pos=strchr(buffer,'\n');
    //*pos = "\0";
    send(sock,buffer,32,0);
    signal(SIGINT, f);
  }
  

}//main
