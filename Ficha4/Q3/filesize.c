#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
   struct stat info;
   if (argc < 2) {
      fprintf(stderr, "usage: %s filename1 filename2 ...\n", argv[0]);
      return EXIT_FAILURE;
   }
   int totalSize = 0, totalBlockSize = 0;
   for(int i = 1; i < argc; i++) {
      if (lstat(argv[i], &info) == -1) {
         fprintf(stderr, "fsize: Can't stat %s\n", argv[i]);
         return EXIT_FAILURE;
      }

      int size = (int)info.st_size;
      int blocks = (int)info.st_blocks;
      int owner = info.st_uid;      // Returns the user id in int format
      char *time = ctime(&info.st_mtime);
      printf("%s size: %d bytes, disk_blocks: %d, owner: %d, last modification: \"%s\"\n", argv[i], size, blocks, owner, time);
      
      totalSize += size;
      totalBlockSize += blocks;
   }
   printf("Total size = %d\nTotal Blocs = %d\n", totalSize, totalBlockSize);
   return EXIT_SUCCESS;
}
