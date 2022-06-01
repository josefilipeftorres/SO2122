#include <stdio.h>
#include <ctype.h>
#include <string.h>

void flag_null(char *file) {
    FILE *fp = fopen(file, "r");
    char c;
    while((c = fgetc(fp)) != EOF) {
        putchar(c);
    }
    fclose(fp);
}

void flag_X(char *first, char *second) {
    FILE *fp = fopen(second, "r");
    if(strcmp(first, "-u") == 0) {
        char c;
        while ((c = fgetc(fp)) != EOF) {
            putchar(toupper(c));
        }
    } else if(strcmp(first, "-l") == 0) {
        char c;
        while ((c = fgetc(fp)) != EOF) {
            putchar(tolower(c));
        }
    } else 
        flag_null(second);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    
    switch (argc) {
        case 1:
            printf("No arguments!\n");
            break;
        case 2:
            flag_null(argv[1]);
            break;
        default:
            flag_X(argv[1], argv[2]);
            break;
    }
    return 0;
}