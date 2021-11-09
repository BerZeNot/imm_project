#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define STACK_EMPTY -3

typedef struct ponto{
    int x;
    int y;
} Ponto;


typedef struct TStackPoint TStackPoint;

TStackPoint *stack_create();

int stack_free(TStackPoint *st);

int stack_top(TStackPoint *st, Ponto *p);

int stack_push(TStackPoint *st, Ponto p);

int stack_pop(TStackPoint *st);

int stack_empty(TStackPoint *st);

int stack_print(TStackPoint *st);


