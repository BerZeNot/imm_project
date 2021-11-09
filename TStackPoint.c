#include <stdio.h>
#include <stdlib.h>
#include "TStackPoint.h"

typedef struct St_NodePoint St_NodePoint;



struct St_NodePoint{
    Ponto p;
    St_NodePoint *next;
};

struct TStackPoint{
    St_NodePoint *top;
};

TStackPoint *stack_create(){
    TStackPoint *stp;
    stp = malloc(sizeof(TStackPoint));
    if(stp == NULL){
        free(stp);
        return NULL;
    }

    stp->top = NULL;
    return stp;
}

int stack_free(TStackPoint *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    else{
        free(st);
        return SUCCESS;
    }
}

int stack_top(TStackPoint *st, Ponto *p){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    else{
        if(st->top == NULL)
            return STACK_EMPTY;
        else{
            *p = st->top->p;
        }
    }
}

int stack_push(TStackPoint *st, Ponto p){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    else{

        St_NodePoint *stn;
        stn = malloc(sizeof(St_NodePoint));
        if(stn == NULL)
            return OUT_OF_MEMORY;
        
        else{
            stn->p = p;
            stn->next = st->top;
            st->top = stn;
            return SUCCESS;
        }
    }
}

int stack_pop(TStackPoint *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    else{
        St_NodePoint *aux;
        aux = st->top;
        st->top = st->top->next;
        free(aux);
        return SUCCESS;
    }
}

int stack_empty(TStackPoint *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    else{
        if(st->top == NULL)
            return 1;
        else
            return 0;
    }
}

int stack_print(TStackPoint *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    else{
        St_NodePoint *aux;
        aux = st->top;
        while(aux != NULL){
            printf("(x:%d | y: %d)\n",aux->p.x, aux->p.y);
            aux = aux->next;
        }
        return SUCCESS;
    }
}