#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PP_RD 0
#define PP_WR 1

#define LINESIZE 256

int main(int argc, char *argv[])
{
   int n, r, fd[2];
   pid_t pid;
   char line[LINESIZE];

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
      printf("P=> Parent process with pid %d\n", getpid());
      printf("P=> Messaging the child process (pid %d):\n", pid);
      snprintf(line, LINESIZE, "Hello! I'm your parent pid %d!\n", getpid());
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
      printf("C=> Child process with pid %d\n", getpid());
      printf("C=> Receiving message from parent (pid %d):\n", getppid());
      if ((n = read(fd[PP_RD], line, LINESIZE)) < 0)
      {
         fprintf(stderr, "Unable to read from pipe: %s\n", strerror(errno));
      }
      close(fd[PP_RD]);
      /* write message from parent */
      write(STDOUT_FILENO, line, n);
      /* exit gracefully */
      exit(EXIT_SUCCESS);
   }
}
