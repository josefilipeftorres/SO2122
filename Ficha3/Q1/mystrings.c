#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_SIZE 100

int main(int argc, char* argv[]) {
    if(argc == 2) {
        char *s = (char *)malloc(MAX_STRING_SIZE * sizeof(char));
        s = argv[1]; // strcpy(s, argv[1]);
        
        // Transforma uma string dada na sua versão em minuscula
        char *res = (char *)malloc(strlen(s) * sizeof(char));
        for(int i = 0; i < strlen(s); i++) {
            res[i] = tolower(s[i]);
        }
        printf("Original: \"%s\" tolower: \"%s\"\n", s, res);
    } else if(argc == 3) {
        char *s1 = (char *)malloc(MAX_STRING_SIZE * sizeof(char));
        char *s2 = (char *)malloc(MAX_STRING_SIZE * sizeof(char));

        s1 = argv[1];
        s2 = argv[2];
        
        // Verifica se s1 ocorre em s2
        if(strstr(s2,s1) != NULL) {
            // Conta quantas vezes s1 ocorre em s2
            int count = 0;
            char *lastfind = NULL;
            for (char *p = s2; (lastfind = strstr(p, s1)); p = lastfind + 1)
                count++;
            printf("%s contains %s %dx\n", s2, s1, count);
        } else
            printf("%s doesn't contain %s\n", s2, s1);        
    } else {
        printf("Invalid arguments!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}