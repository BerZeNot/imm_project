#include "imm_resources.h"

int open(char const *filename){
    // printf("Filename: %s\n", filename);
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        fclose(fp);
        return CANT_OPEN_FILE;
    }
    char imageHeader[3];
    int pixelValue, imageWidth, imageHeight, maxColorValue;
    fscanf(fp, "%s", imageHeader); // Lê o dado da primeira linha da imagem
    fscanf(fp, "%d", &imageWidth); // Lê a largura da imagem
    fscanf(fp, "%d", &imageHeight); // Lê a altura da imagem
    fscanf(fp, "%d", &maxColorValue ); // Lê o valor máximo que um píxel terá na imagem
    for(int i=0; i<imageHeight; i++){
        for(int j = 0; j<imageWidth; j++){
            fscanf(fp, "%d", &pixelValue);
            if(pixelValue < 10)
                printf("%d   ", pixelValue);
            else if(pixelValue < 100)
                printf("%d  ", pixelValue);
            else
                printf("%d ", pixelValue);
        }
        printf("\n");
    }

    fclose(fp);
    return SUCCESS;
}

int convert(char const *filename, char const *outfile_name){
    FILE *inFile, *outFile;
    inFile = fopen(filename, "r");
    if(inFile == NULL)
        return CANT_OPEN_FILE;
    
    outFile = fopen(outfile_name, "wb");
    if(outFile == NULL)
        return CANT_CREATE_FILE;
    
    char imageHeader[3];
    int pixelValue, imageWidth, imageHeight, maxColorValue;
    fscanf(inFile, "%s", imageHeader); // Lê o dado da primeira linha da imagem de entrada
    fprintf(outFile, "%s\n", imageHeader); // Escreve no arquivo de saída
    
    fscanf(inFile, "%d", &imageWidth); // Lê a largura da imagem
    fscanf(inFile, "%d", &imageHeight); // Lê a altura da imagem
    fprintf(outFile, "%d %d\n", imageWidth, imageHeight); // Escreve a largura e altura da imagem no arquivo de saída
    
    fscanf(inFile, "%d", &maxColorValue ); // Lê o valor máximo que um píxel terá na imagem
    fprintf(outFile, "%d\n", maxColorValue ); // Escreve no arquivo de saída o valor máximo que um píxel terá na imagem
    
    for(int i=0; i<imageHeight; i++){
        for(int j = 0; j<imageWidth; j++){
            fscanf(inFile, "%d", &pixelValue);
            if(pixelValue < 10)
                fprintf(outFile, "%d   ", pixelValue);
            else if(pixelValue < 100)
                fprintf(outFile, "%d  ", pixelValue);
            else
                fprintf(outFile, "%d ", pixelValue);
        }
        fprintf(outFile,"\n");
    }

    fclose(inFile);
    fclose(outFile);

    return SUCCESS;
}

int segment(char const *thr, char const *filename, char const *outfile_name){
    
    // Converte o valor thr que veio como string para inteiro;
    int thrInt = ((int)thr[0]-48)*100 + ((int)thr[1]-48)*10 + ((int)thr[2]-48)*1;
    
    FILE *inFile, *outFile;
    inFile = fopen(filename, "rb");
    if(inFile == NULL)
        return CANT_OPEN_FILE;
    
    outFile = fopen(outfile_name, "wb");
    if(outFile == NULL)
        return CANT_CREATE_FILE;
    
    char imageHeader[3];
    int pixelValue, imageWidth, imageHeight, maxColorValue;
    fscanf(inFile, "%s", imageHeader); // Lê o dado da primeira linha da imagem de entrada
    fprintf(outFile, "%s\n", imageHeader); // Escreve no arquivo de saída
    
    fscanf(inFile, "%d", &imageWidth); // Lê a largura da imagem
    fscanf(inFile, "%d", &imageHeight); // Lê a altura da imagem
    fprintf(outFile, "%d %d\n", imageWidth, imageHeight); // Escreve a largura e altura da imagem no arquivo de saída
    
    fscanf(inFile, "%d", &maxColorValue ); // Lê o valor máximo que um píxel terá na imagem
    fprintf(outFile, "%d\n", maxColorValue ); // Escreve no arquivo de saída o valor máximo que um píxel terá na imagem

    for(int i=0; i<imageHeight; i++){
        for(int j = 0; j<imageWidth; j++){
            fscanf(inFile, "%d", &pixelValue);
            if(pixelValue >= thrInt)
                fprintf(outFile, "%d ", 255);
            else
                fprintf(outFile, "%d   ", 0);
        }
        fprintf(outFile,"\n");
    }

    fclose(inFile);
    fclose(outFile);


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