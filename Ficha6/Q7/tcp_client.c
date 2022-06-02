#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>

#define MAX_BUF_SIZE 256

int main(int argc, char *argv[]) {
   int sock, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   char buffer[MAX_BUF_SIZE];

   if (argc < 3) {
      fprintf(stderr, "usage %s hostname port\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   portno = atoi(argv[2]);

   /* create a socket point */
   sock = socket(AF_INET, SOCK_STREAM, 0);

   if (sock < 0) {
      perror("ERROR opening socket");
      exit(EXIT_FAILURE);
   }

   server = gethostbyname(argv[1]);

   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(EXIT_FAILURE);
   }

   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
   serv_addr.sin_port = htons(portno);

   /* connect to the server */
   if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(EXIT_FAILURE);
   }

   /* ask for a message from the user, this message
    * will be read by server
    */

   printf("Please enter the message: ");
   bzero(buffer, MAX_BUF_SIZE);
   fgets(buffer, MAX_BUF_SIZE - 1, stdin);

   /* send message to the server */
   n = write(sock, buffer, strlen(buffer));

   if (n < 0) {
      perror("ERROR writing to socket");
      exit(EXIT_FAILURE);
   }

   /* Now read server response */
   bzero(buffer, MAX_BUF_SIZE);
   n = read(sock, buffer, MAX_BUF_SIZE - 1);

   if (n < 0) {
      perror("ERROR reading from socket");
      exit(EXIT_FAILURE);
   }

   printf("%s\n",buffer);

   exit(EXIT_SUCCESS);
}
