#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
   pid_t pid;
   int value = 0;

   if ((pid = fork()) < 0 ) {
      printf("%s: cannot fork()\n", argv[0]);
      return EXIT_FAILURE;
   }
   else if (pid == 0) {
      /* child process */
      value = 1;
      printf("CHILD: value = %d, addr = %p\n", value, &value);
      return EXIT_SUCCESS;
   }
   else {
      /* parent process */
      if (waitpid(pid, NULL, 0) < 0) {
         printf("%s: cannot wait for child\n", argv[0]);
         return EXIT_FAILURE;
      }
      printf("PARENT: value = %d, addr = %p\n", value, &value);
      return EXIT_SUCCESS;
   }
}
