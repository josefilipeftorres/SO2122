#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define DATA "Such is the nature of evil. \
Out there in the vast ignorance of the world it \
festers and spreads. A shadow that grows in the dark. \
A sleepless malice as black as the oncoming wall of night. \
So it ever was. So will it always be. \
In time all foul things come forth."

/*
 * this is the client side
 */
int main(int argc, char *argv[]) {
   int sock;
   struct sockaddr_in name;
   struct hostent *hp;

   /* create socket on which to send */
   if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("opening datagram socket");
      return EXIT_FAILURE;
   }

   /* destination is constructed from hostname
      and port both given in the command line */
   if ((hp = gethostbyname(argv[1])) == 0) {
      fprintf(stderr, "%s: unknown host\n", argv[1]);
      return EXIT_FAILURE;
   }
   memcpy(&name.sin_addr, hp->h_addr, hp->h_length);
   name.sin_family = AF_INET;
   name.sin_port = htons(atoi(argv[2]));

   /* connect to given port */
   if(connect(sock, (struct sockaddr *)&name, sizeof(name)) < 0) {
      perror("connecting to server socket");
      return EXIT_FAILURE;
   }

   /* send message */
   if (write(sock, DATA, sizeof(DATA)) < 0)
      perror("sending datagram message");

   close(sock);

   return EXIT_SUCCESS;
}
