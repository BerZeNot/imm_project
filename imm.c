#include <stdio.h>
#include <string.h>
#include "imm_resources.h"

int main(int argc, char const *argv[]){
    if(argv[1] == NULL){
        printf("No command informed\n");
        return -1;
    }

    if(strcmp(argv[1], "-open") == 0){
        open(argv[2]);
    }

    else if(strcmp(argv[1], "-convert") == 0){
        int resposta;
        resposta = convert(argv[2], argv[3]);
        printf("Resposta: %d\n", resposta);
    }
    
    else if(strcmp(argv[1], "-segment") == 0){
        segment(argv[2], argv[3]);
    }

    else if(strcmp(argv[1], "-cc") == 0){
        connected_component(argv[2], argv[3]);
    }

    else if(strcmp(argv[1], "-lab") == 0){
        lab(argv[2], argv[3]);
    }

    else if(strcmp(argv[1], "-help") == 0){
        help();
    }

    else{
        printf("O comando \"%s\" não existe!\n", argv[1]);
    }
    return 0;
}