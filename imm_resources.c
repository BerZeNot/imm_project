#include "imm_resources.h"
#include "TMat2D.h"
#include <string.h>


// loads a file into a matrix;
int loadFile(FILE *fp, TMat2D **matrix, int nRows, int nCols);

// writes data from a matrix to a file;
int writefile(char const *filename, TMat2D *matrixData, int nRows, int nCols);

int getMatrixSize(char const *filename, int *ncols, int *nRows);

int openTxt(char const *filename){
    
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        fclose(fp);
        return CANT_OPEN_FILE;
    }
    
    char pixelChar;
    while(!feof(fp)){
        fscanf(fp, "%c", &pixelChar);
        printf("%c", pixelChar);
    }
    fclose(fp);
    return SUCCESS;
}

int openImm(char const *filename){
    printf("Open binary\n");
    return SUCCESS;
}

int convert(char const *filename, char const *outfile_name){
    FILE *inFile;
    inFile = fopen(filename, "r");
    if(inFile == NULL){
        fclose(inFile);
        return CANT_OPEN_FILE;
    }
    
    // Calcula o número de linhas e colunas da imagem
    int numberRows, numberCols;
    getMatrixSize(filename, &numberCols, &numberRows);

    // Instancia uma matriz e carrega os dados do arquivo nela
    TMat2D *inFileData;
    loadFile(inFile, &inFileData, numberRows, numberCols);
    
    // mat2D_print_matrix(inFileData);

    // Fecha o arquivo de entrada
    fclose(inFile);
    // Escreve os dados da matriz em um novo arquivo imm.
    writefile(outfile_name, inFileData,  numberRows, numberCols);

    // printf("Ncols: %d, nRows: %d\n", numberCols, numberRows);
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


int getMatrixSize(char const *filename, int *ncols, int *nRows){
    FILE *fp = fopen(filename,"r");
    if(fp == NULL){
        return CANT_OPEN_FILE;
    }
    char pixelChar;
    int i = 1, j = 1;
    while(!feof(fp)){
        fscanf(fp, "%c", &pixelChar);
        if(pixelChar == '\n')
            i++;
        if(pixelChar == '\t')
            j++;
    }
    *nRows = i;
    *ncols = (j/i)+1;
    fclose(fp);
}

// Gets the 3 last characters from the file name
void getExtention(const char *fileName, int size, char *outVector){
    for(int i = 1; i<=3; i++){
        outVector[i-1] = fileName[(size-4)+i];
    }
}


void help(){
    printf("<< Possible commands >>\n");
    printf("-open (./imm -open filename.txt) \n");
    printf("-convert (./imm -convert filename.txt outfilename.imm)\n");
    printf("-segment (./imm -segment filename.txt outfilename.imm)\n");
    printf("-cc (./imm -cc filename.txt outfilename.imm)\n");
    printf("-lab (./imm -lab filename.txt outfilename.imm)\n");
}


// Auxiliary Functions

// Loads a file data into a matrix;
int loadFile(FILE *fp, TMat2D **inFileData, int nRows, int nCols){
    *inFileData = mat2D_create(nRows, nCols);
    if(inFileData == NULL)
        return CANT_OPEN_FILE;
    
    double pixelValue;

    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            fscanf(fp, "%lf", &pixelValue);
            // printf("%.lf ", pixelValue);
            mat2D_set_value(*inFileData,i, j,pixelValue);
        }
    }
    
    return SUCCESS;
}

// Writes data from a matrix to a file;
int writefile(char const *filename, TMat2D *matrixData, int nRows, int nCols){
    FILE *fp = fopen(filename, "wb");
    if(fp == NULL)
        return CANT_CREATE_FILE;

    fwrite(&nRows, sizeof(int), 1, fp);
    fwrite(&nCols, sizeof(int), 1, fp);
    double pixel;
    int pixelInt;
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            mat2D_get_value(matrixData, i, j, &pixel);
            pixelInt = pixel;
            // printf("%d ", pixelInt);
            fwrite(&pixelInt, sizeof(int), 1, fp);
        }
    }

    fclose(fp);
    return SUCCESS;
}