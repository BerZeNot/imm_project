#include <stdio.h>
#include <string.h>
#include "imm_resources.h"

void getExtention(const char *fileName, int size, char *outVector);

int main(int argc, char const *argv[]){
    if(argv[1] == NULL){
        printf("No command informed\n");
        return -1;
    }

    if(strcmp(argv[1], "-open") == 0){

        if(argv[2] == NULL){
            printf("Inform the file name!\n");
            return MISSING_FILENAME;
        }

        char extention[3];
        getExtention(argv[2], strlen(argv[2]), extention);
        
        if(strcmp(extention, "imm") == 0)
            openImm(argv[2]);

        else if(strcmp(extention, "pgm") == 0)
            openTxt(argv[2]);

        else if(strcmp(extention, "txt") == 0)
            openTxt(argv[2]);
        
        else{
            printf("Format is not supported!\n");
            printf("Try some file with extensions .txt, .pgm or .imm.\n");
            return FORMAT_NOT_SUPPORTED;
        }
    }

    else if(strcmp(argv[1], "-convert") == 0){
        convert(argv[2], argv[3]);
    }
    
    else if(strcmp(argv[1], "-segment") == 0){
        segment(argv[2], argv[3], argv[4]);
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