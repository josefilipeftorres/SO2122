#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>

#define SERV_PORT 5001
#define MAX_BUF_SIZE 256

void doprocessing (int sock);

int main( int argc, char *argv[] ) {
   int sock, new_sock, pid;
   int true = 1;
   struct sockaddr_in serv_addr, cli_addr;
   socklen_t cli_len;

   /* first call to socket() function */
   sock = socket(AF_INET, SOCK_STREAM, 0);

   if (sock < 0) {
      perror("ERROR opening socket");
      exit(EXIT_FAILURE);
   }

   /* initialize socket structure (allow socket reuse) */
   setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));

   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(SERV_PORT);

   /* now bind the host address using bind() call: sock <-> serv_addr */
   if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(EXIT_FAILURE);
   }

   /* now start listening for the clients, here
    * process will go in sleep mode and will wait
    * for the incoming connection
    */
   listen(sock, 5);
   cli_len = sizeof(cli_addr);

   while (1) {
      new_sock = accept(sock, (struct sockaddr *) &cli_addr, &cli_len);
      if (new_sock < 0) {
         perror("ERROR on accept");
         break;
      }

      /* Create child process */
      pid = fork();

      if (pid < 0) {
         perror("ERROR on fork");
         close(new_sock);
         break;
      }

      if (pid == 0) {
         /* This is the client process */
         close(sock);
         doprocessing(new_sock);
         exit(EXIT_SUCCESS);
      }
      else {
         close(new_sock);
      }

   } /* end of while */

   close(sock);
   exit(EXIT_FAILURE);
}

void doprocessing (int sock) {
   int n;
   char buffer[MAX_BUF_SIZE];
   char reply[] = "I got your message";

   bzero(buffer, MAX_BUF_SIZE);
   n = read(sock, buffer, MAX_BUF_SIZE - 1);

   if (n < 0) {
      perror("ERROR reading from socket");
      exit(EXIT_FAILURE);
   }

   printf("Here is the message: %s\n",buffer);
   n = write(sock, reply, sizeof(reply));

   if (n < 0) {
      perror("ERROR writing to socket");
      exit(EXIT_FAILURE);
   }
   close(sock);
}
