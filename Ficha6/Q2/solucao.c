#include <sys/wait.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define SOCK0 0
#define SOCK1 1
#define BUFFSIZE 1024

int main(int argc, char *argv[])
{
    int sockets[2];
    pid_t pid;

    if (argc < 2)
    {
        printf("usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) == -1)
    {
        perror("opening stream socket pair");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        /* this is the child */
        close(sockets[SOCK0]);

        /*
         * repeat until read returns 0 (pipe closes on parent side):
         *   read 1 block from parent
         *   read block back to parent
         */
        int nbytes;
        char buf[BUFFSIZE];
        while ((nbytes = read(sockets[SOCK1], buf, BUFFSIZE)) > 0)
            write(sockets[SOCK1], (buf), nbytes);
        close(sockets[SOCK1]);

        /* return gracefully */
        exit(EXIT_SUCCESS);
    }
    else
    {
        /* this is the parent */
        close(sockets[SOCK1]);
        int fd = open(argv[1], O_RDONLY);

        /*
         * repeat until EOF:
         *   read file 1 block at a time
         *   send block to child
         *   read block back from child
         *   print block
         */
        int nbytes;
        char buf[BUFFSIZE];
        while ((nbytes = read(fd, buf, BUFFSIZE)) > 0)
        {
            write(sockets[SOCK0], buf, nbytes);
            if ((nbytes = read(sockets[SOCK0], buf, BUFFSIZE)) > 0)
                write(STDOUT_FILENO, (buf), nbytes);
        }
        close(sockets[SOCK0]);

        /* wait for child and exit */
        waitpid(pid, NULL, 0);

        /* return gracefully */
        exit(EXIT_SUCCESS);
    }
}