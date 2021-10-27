#include "imm_resources.h"

int open(char const *filename){
    // printf("Filename: %s\n", filename);
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        fclose(fp);
        return CANT_OPEN_FILE;
    }
    char pixelValue[255];
    int cont = 0; // é incrementado até 3 para ignorar as 3 primeiras strings do arquivo.
    while(!feof(fp)){
        fscanf(fp,"%s", pixelValue);
        if(cont < 3){ // Se o valor do contador for menor que 3, o laço não vai ler a string
            cont++;   // isso vai fazer com que ele ignore as strings de informação da imagem e 
            continue; // imprima apenas os valores dos pixels da imagem.
        } else
            printf("%s ",pixelValue);
    }
    fclose(fp);
    return SUCCESS;
}

int convert(char const *filename, char const *outfile_name){
    printf("Filename: %s\n", filename);
    printf("Outfile name: %s\n", outfile_name);
    return SUCCESS;
}

int segment(char const *filename, char const *outfile_name){
    printf("Filename: %s\n", filename);
    printf("Outfile name: %s\n", outfile_name);
    return SUCCESS;
}

int connected_component(char const *filename, char const *outfile_name){
    printf("Filename: %s\n", filename);
    printf("Outfile name: %s\n", outfile_name);
    return SUCCESS;
}

int lab(char const *filename, char const *outfile_name){
    printf("Filename: %s\n", filename);
    printf("Outfile name: %s\n", outfile_name);
    return SUCCESS;
}

void help(){
    printf("<< Possible commands >>\n");
    printf("-open (./imm -open filename.txt) \n");
    printf("-convert (./imm -convert filename.txt outfilename.imm)\n");
    printf("-segment (./imm -segment filename.txt outfilename.imm)\n");
    printf("-cc (./imm -cc filename.txt outfilename.imm)\n");
    printf("-lab (./imm -lab filename.txt outfilename.imm)\n");
}