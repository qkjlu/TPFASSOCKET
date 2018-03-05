// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define PORT 10000

int main(void) {

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
  while (1){
    pid_t pid;
    pid = fork();
	
    if (pid == 0)
      {
        csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
	char str[32];
	strcpy("yo",str);
	printf("%s",str);
        printf("Un client se connecte avec la socket %d de %s:%d\n",
	       csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
	char buffer[32];
	
	recv(csock,buffer,32,0 );
	printf(buffer);
        
	kill(getpid(), 9);
      }
    else {
      wait();
    }
  }

  /* Fermeture de la socket client et de la socket serveur */
  close(csock);
  close(sock);
  return EXIT_SUCCESS;

}//main
