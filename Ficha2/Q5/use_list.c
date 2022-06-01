#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main() {
    list *l = list_new_random(10,10);
    printf("List l:\n");
    list_print(l);
    list_add_first(42,l);
    list_add_last(43,l);
    list_print(l);
    printf("First elem = %d Last elem = %d Size = %d\n\n", list_get_first(l), 
                                                       list_get_last(l),
                                                       list_size(l));
    
    list_remove_first(l);
    list_print(l);
    printf("First elem = %d Last elem = %d Size = %d\n\n", list_get_first(l), 
                                                       list_get_last(l),
                                                       list_size(l));
    
    list_remove_last(l);
    list_print(l);
    printf("First elem = %d Last elem = %d Size = %d\n\n", list_get_first(l), 
                                                       list_get_last(l),
                                                       list_size(l));
    list *l1 = list_new_random(1,10);
    printf("Lista 1:\n");
    list_print(l1);
    printf("%d %d %d\n", list_get_first(l1), list_get_last(l1), list_size(l1));
    list_remove_last(l1);
    list_print(l1);
    return 0;
}