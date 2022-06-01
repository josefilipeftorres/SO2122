#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int f(char* content) {
   // char str[8];
   char *str = (char *)malloc(strlen(content) * sizeof(char));
   int result = 2;
   (void)strcpy(str, content);
   return result;
}

int main(int argc, char* argv[]) {
   if (argc == 2)
      printf("result = %d\n", f(argv[1]));
   return EXIT_SUCCESS;
}
