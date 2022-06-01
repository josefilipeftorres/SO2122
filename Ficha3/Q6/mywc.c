#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flag_c(char *file) {
    FILE *fp = fopen(file, "r");
    
    fseek(fp, 0L, SEEK_END);
    long nBytes = ftell(fp);

    printf("%ld\n", nBytes);
    fclose(fp);
}

void flag_w(char *file) {
    FILE *fp = fopen(file, "r");
    int count = 0, word = 0;
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        if(c == '\n' || c == ' ') {
            word = 0;
        } else {
            if(!word) {
                count++;
                word = 1;
            }
        }
    }
    printf("%d\n", count);
    fclose(fp);
}

void flag_l(char *file) {
    FILE *fp = fopen(file, "r");
    int count = 0;
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        if(c == '\n') count++;
    }
    printf("%d\n", count);
    fclose(fp);
}

void flag_X(char *flag, char *file) {
    if(strcmp(flag, "-w") == 0) flag_w(file);
    else if(strcmp(flag, "-l") == 0) flag_l(file);
    else flag_c(file);
}

int main(int argc, char *argv[]) {
    switch (argc) {
        case 1:
            printf("Invalid arguments!\n");
            break;
        case 3:
            flag_X(argv[1], argv[2]);
            break;
        default:
            flag_c(argv[1]);
            break;
    }
    return EXIT_SUCCESS;
}
