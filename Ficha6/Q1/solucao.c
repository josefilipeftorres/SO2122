#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define PP_RD 0
#define PP_WR 1
#define LINESIZE 256
#define BUFFERSIZE 256

int main(int argc, char *argv[])
{
    int n, r, fd[2];
    pid_t pid;
    char line[LINESIZE];

    if(argc < 2) {
        perror("Not enough arguments!\n");
        exit(EXIT_FAILURE);
    }

    int file = open(argv[1], O_RDONLY);
    if (pipe(fd) < 0)
    {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        /* parent */
        close(fd[PP_RD]);
        if ((r = write(fd[PP_WR], line, strlen(line))) < 0)
        {
            fprintf(stderr, "Unable to write to pipe: %s\n", strerror(errno));
        }
        close(fd[PP_WR]);
        /* wait for child and exit */
        if (waitpid(pid, NULL, 0) < 0)
        {
            fprintf(stderr, "Cannot wait for child: %s\n", strerror(errno));
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        /* child */
        close(fd[PP_WR]);
        if ((n = read(fd[PP_RD], line, LINESIZE)) < 0)
        {
            fprintf(stderr, "Unable to read from pipe: %s\n", strerror(errno));
        }
        close(fd[PP_RD]);
        
        /* write message from parent */
        char buff[BUFFERSIZE];
        long nbytes;
        while((nbytes = read(file, buff, BUFFERSIZE)) != 0)
            write(STDOUT_FILENO, buff, nbytes);

        /* exit gracefully */
        exit(EXIT_SUCCESS);
    }
}
