#include <stdio.h>
#include <string.h>
#include "TImage.h"
#include "imm_resources.h"

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
        get_extention(argv[2], strlen(argv[2]), extention);
        
        if(strcmp(extention, "imm") == 0 || strcmp(extention, "txt") == 0){
            int response;
            response = open(argv[2]);
            if(response == 0)
                return response;
        }

        else{
            printf("Format is not supported!\n");
            printf("Try some file with extensions .txt or .imm.\n");
            return UNSUPPORTED_FILE_FORMAT;
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