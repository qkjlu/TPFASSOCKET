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
  connect(sock, (struct sockaddr*)&sin, sizeof(sin));
 
  printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr),
         htons(sin.sin_port));
  char buffer[32];
  char *pos;
  while(1) {
    printf("Entrer la chaine de caractère à envoyer au serveur \n");
    fgets(buffer,32,stdin);
    pos=strchr(buffer,'\n');
    *pos = "\0";
    send(sock,buffer,32,0);
    signal(SIGINT, f);
  }
  

}//main
