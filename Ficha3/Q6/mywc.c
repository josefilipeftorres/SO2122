#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getContent(char *f1) {
    FILE *file;
    char *text;
    long numbytes;

    file = fopen(f1,"r");
    if(!file) {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0L, SEEK_END);
    numbytes = ftell(file);
    fseek(file, 0L, SEEK_SET);
    
    text = (char*)calloc(numbytes, sizeof(char));

    fread(text, sizeof(char), numbytes, file);

    if (!text)
        return NULL;

    return text;
}

void flag_c(char *file) {
    FILE *fp = fopen(file, "r");
    
    fseek(fp, 0L, SEEK_END);
    long nBytes = ftell(fp);

    printf("%ld\n", nBytes);
    fclose(fp);
}

void flag_w(char *file) {
    FILE *fp = fopen(file, "r");
    
    fseek(fp, 0L, SEEK_END);
    long nbytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    char *text = (char *)malloc(nbytes * sizeof(char));
    fread(text,sizeof(char),nbytes,fp);

    int count = 1;
    for(int i = 0; i < strlen(text); i++) 
        if(text[i] == ' ') count++;
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
