#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if(argc == 3) {
        FILE *f1 = fopen(argv[1], "r");
        FILE *f2 = fopen(argv[2], "w");

        if(f1 == NULL || f2 == NULL) {
            printf("Error opening the file!\n");
            return EXIT_FAILURE;
        }
        char *text;
        fseek(f1, 0L, SEEK_END);    // Move file pointer to the end of the file
        long nBytes = ftell(f1);    // Find the position of the file pointer (size of the file to use in fread and fwrite)
        fseek(f1, 0L, SEEK_SET);    // Move file pointer back to the start of the file

        text = (char*)malloc(nBytes * sizeof(char));    // Create the space for the data with size nBytes
        fread(text, sizeof(char), nBytes, f1);          // Reads the data from f1 and store it in text
        fwrite(text, sizeof(char), nBytes, f2);         // Writes in f2 the data stored in text
        fclose(f1);
        fclose(f2);
        return EXIT_SUCCESS;
    } else {
        printf("Error: Invalid arguments!\n");
        return EXIT_FAILURE;
    }
}