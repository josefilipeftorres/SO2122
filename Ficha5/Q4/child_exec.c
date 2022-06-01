#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  pid_t pid;
  
  /* fork a child process */
  if ((pid = fork()) < 0 ) {
    printf("%s: cannot fork()\n", argv[0]);
    return EXIT_FAILURE;
  } else if (pid == 0) { 
    /* child process */
    if (execlp(argv[1],argv[1],NULL) < 0) {
      printf("bummer, did not exec %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  } else { 
    /* parent process */
    if (waitpid(pid, NULL, 0) < 0) {
      printf("%s: cannot wait for child\n", argv[0]);
      return EXIT_FAILURE;
    }
    printf("child exited\n");
  }
  return EXIT_SUCCESS;
}
