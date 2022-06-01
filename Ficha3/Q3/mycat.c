#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    for(int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");

        if(f == NULL) {
            printf("mycat: %s: No such file or directory\n", argv[i]);
            continue;
        }

        char c;
        while ((c = fgetc(f)) != EOF) {
            fputc(c, stdout);
        }
        fclose(f);
    }
    return EXIT_SUCCESS;
}
