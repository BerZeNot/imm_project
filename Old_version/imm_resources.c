#include <string.h>
#include <stdlib.h>
#include "imm_resources.h"
#include "TMat2D.h"


// loads a file into a matrix;
int loadFile(FILE *fp, TMat2D **matrix, int nRows, int nCols);

// writes data from a matrix to a file;
int writefile(char const *filename, TMat2D *matrixData, int nRows, int nCols);

int getMatrixSize(char const *filename, int *ncols, int *nRows);

int getMatrizSizeFromBin(FILE *fp, int *ncols, int *nRows);

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
    FILE *fp = fopen(filename, "rb");
    if(fp == NULL){
        fclose(fp);
        return CANT_OPEN_FILE;
    }
    int nrows, ncols;

    fread(&nrows,sizeof(int), 1, fp);
    fread(&ncols,sizeof(int), 1, fp);
    printf("Nrows: %d\nNcols: %d\n", nrows, ncols);


    int pixel;
    for(int i=0; i<nrows; i++){
        for(int j=0; j<ncols; j++){
            fread(&pixel, sizeof(int), 1, fp);
            if(pixel < 10)
                printf("%d   ", pixel);
            else if(pixel < 100)
                printf("%d  ", pixel);
            else
                printf("%d ", pixel);
        }
        printf("\n");
    }

    fclose(fp);
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
    int thrInt = atoi(thr);
    
    // Verifica qual é a extensão do arquivo
    char fileType[3];
    getExtention(filename, strlen(filename), fileType);
    
    // Numero de linhas e colunas do arquivo
    int numberRows, numberCols;
    
    // Abre o arquivo
    FILE *fp;
    if(strcmp(fileType, "imm")==0){
        fp = fopen(filename, "rb");
        if(fp == NULL){
            fclose(fp);
            return CANT_OPEN_FILE;
        }
        getMatrizSizeFromBin(fp, &numberCols, &numberRows);
        printf("Opened like binary\n");
        printf("NumberCols: %d, NumberRows: %d", numberCols, numberRows);
    }
    else if(strcmp(fileType, "txt")==0){
        fp = fopen(filename, "r");
        if(fp == NULL){
            fclose(fp);
            return CANT_OPEN_FILE;
        }
        getMatrixSize(filename, &numberCols, &numberRows);
        printf("Opened like binary\n");
        printf("NumberCols: %d, NumberRows: %d", numberCols, numberRows);
    } 

    // Carrega os dados dele para uma matriz;   

    TMat2D *inFileData;
    loadFile(fp, &inFileData, numberRows, numberCols);

    // Fecha o arquivo de entrada
    fclose(fp);
    return 0;
    // Faz o thresholding dos dados na matriz
    double pixelInMatrix;
    for(int i=0; i<numberRows; i++){
        for(int j=0; j<numberCols; j++){
            mat2D_get_value(inFileData,i,j,&pixelInMatrix);
            if(pixelInMatrix > (double)thrInt){
                mat2D_set_value(inFileData,i,j,1.0);
            }
            else {
                mat2D_set_value(inFileData,i,j,0.0);
                printf("%lf ", pixelInMatrix);
            }
        }
    }

    // Escreve os dados da matriz no outfile
     writefile(outfile_name, inFileData, numberRows, numberCols);
     
    // retorna sucesso
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

// Pega a quantidade de colunas e linnhas de pixels da imagem texto
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

// Pega a quantidade de colunas e linnhas de pixels da imagem binária
int getMatrizSizeFromBin(FILE *fp, int *ncols, int *nRows){
    fread(nRows, sizeof(int), 1, fp);
    fread(ncols, sizeof(int), 1, fp);
}

// Gets the 3 last characters from the file name
void getExtention(const char *fileName, int size, char *outVector){
    for(int i = 1; i<=3; i++){
        outVector[i-1] = fileName[(size-4)+i];
    }
}

// exibe a ajuda do programa
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
    char fileType[3];
    getExtention(filename,strlen(filename),fileType);


    // Abre o arquivo como binário ou como texto
    FILE *fp;
    if(strcmp(fileType, "imm")==0){
        fp = fopen(filename, "wb");
    }
    else if(strcmp(fileType, "txt")==0){
        fp = fopen(filename, "w");
    }

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