# Sistemas de Operação

## Q2

- The destination string (`str`) is contained in a 8 chars buffer. So, the string can only be of 8 chars length max or else the src string will be copied to the destination without the NULL terminator

- To solve this problem:
    - We could use the function `strlcpy` and specify the destiny size, while making sure that the string will be null terminated.
    - Or `char *str = (char *)malloc(strlen(content) * sizeof(char));`