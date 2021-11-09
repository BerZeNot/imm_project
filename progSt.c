#include <stdio.h>
#include <stdlib.h>
#include "TStackPoint.h"

int main(){
    TStackPoint *st;
    Ponto p1, p2;
    p1.x = 10;
    p1.y = 12;
    p2.x = 22;
    p2.y = 33;
    st = stack_create();
    if(st == NULL)
        printf("Cant create stack");

    if(stack_empty(st))
        printf(" --> Stack empty!\n");
    else
        printf(" --> Stack isn't empty!\n");

    
    int result = stack_push(st, p1);
    result = stack_push(st, p2);
    printf("Result: %d\n", result);
    stack_print(st);
    stack_pop(st);
    stack_print(st);
    if(stack_empty(st))
        printf(" --> Stack empty!\n");
    else
        printf(" --> Stack isn't empty!\n");
    printf("End of program\n");
    return 0;
}
