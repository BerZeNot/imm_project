
#include "TImage.h"

struct TImage
{
    int nrows; // número de linhas
    int ncolumns; // número de colunas
    int *data; // ponteiro para os dados da matriz
};

TImage *image_create(int nrows, int ncolumns){
    TImage *image;
    image = malloc(sizeof(TImage));
    if (image != NULL){
        image->data = malloc(nrows*ncolumns*sizeof(int));
        if (image->data != NULL){
            image->ncolumns = ncolumns;
            image->nrows = nrows;
        } else {
            free(image);
            return NULL;
        }
    }
    return image;
}

int image_free(TImage *image){
    if(image == NULL){
        return -1;
    } else {
        free(image->data);
        free(image);
        return 0;
    }
}

int image_print(TImage *image){
    if(image == NULL)
        return -1;

    for(int i=0; i<image->nrows; i++){
        for(int j=0; j<image->ncolumns; j++){
            int pos = j * image->nrows + i;
            int pixelData = image->data[pos];
            if(pixelData < 10)
                printf("%d   ",pixelData);
            else if(pixelData < 100)
                printf("%d  ",pixelData);
            else
                printf("%d ",pixelData);
        }
        printf("\n");   
    }
}

int image_load_data(TImage *image, const char *filename){
    if(image == NULL)
        return INVALID_NULL_POINTER;
    
    FILE *fp;
    
    int respostaOpenFile;
    respostaOpenFile = open_file(&fp, filename);
    if(fp == NULL)
        return CANT_OPEN_FILE;
    

    char filetype[3];
    get_extention(filename, strlen(filename), filetype);

    int pos=0, pixelValue=0;
    if(strcmp(filetype, "imm")==0){
        // Lê e não utiliza os dois primeiros valores que representam o tamanho da imagem
        fread(&pixelValue,sizeof(int),1,fp);
        fread(&pixelValue,sizeof(int),1,fp);
        for(int i = 0; i < image->nrows; i++){
            for(int j = 0; j < image->ncolumns; j++){
                
                pos = j * image->nrows + i;
                
                fread(&pixelValue,sizeof(int),1,fp); // Lê os dados da imagem binária;
                
                image->data[pos] = pixelValue;
            }
        }

    }
    else if(strcmp(filetype, "txt")==0){
        for(int i = 0; i < image->nrows; i++){
            for(int j = 0; j < image->ncolumns; j++){
                
                pos = j * image->nrows + i;
                
                fscanf(fp, "%d", &pixelValue); // Lê os dados da imagem de texto;
                
                image->data[pos] = pixelValue;
            }
        }

    }
    
    close_file(&fp);

    return SUCCESS;
}

int image_threshold(TImage *image, int thr);

int open_file(FILE **fp, const char *filename){
    char file_extention[3];
    get_extention(filename, strlen(filename), file_extention);

    if(strcmp(file_extention, "txt")==0){
        *fp = fopen(filename, "r");
        if(fp == NULL){
            fclose(*fp);
            return CANT_OPEN_FILE;
        }
        return SUCCESS;
    }

    if(strcmp(file_extention, "imm")==0){
        *fp = fopen(filename, "rb");
        if(fp == NULL){
            fclose(*fp);
            return CANT_OPEN_FILE;
        }
        return SUCCESS;
    }
}

int write_file(TImage *image, const char *outfile_name){
    if(image == NULL)
        return INVALID_NULL_POINTER;
    
    FILE *fp;

    char filetype[3];
    get_extention(outfile_name, strlen(outfile_name), filetype);

    // Abre o arquivo para escrita em modo binário e escreve os dados
    if(strcmp(filetype, "imm") == 0){
        fp = fopen(outfile_name,"wb");
        if(fp == NULL)
            return CANT_OPEN_FILE;


        int auxValue = image->nrows;
        fwrite(&auxValue, sizeof(int), 1, fp);
        auxValue = image->ncolumns;
        fwrite(&auxValue, sizeof(int), 1, fp);

        int pos=0;

        for(int i = 0; i < image->nrows; i++){
            for(int j=0; j < image->ncolumns; j++){
                pos = j * image->nrows + i;
                auxValue = image->data[pos];
                fwrite(&auxValue, sizeof(int), 1, fp);
            }
        }
        

    }
    // Abre o arquivo para escrita em modo texto e escreve os dados
    else if(strcmp(filetype, "txt") == 0){
        fp = fopen(outfile_name,"w");
        if(fp == NULL)
            return CANT_OPEN_FILE;
    }

    fclose(fp);
    return SUCCESS;
}

int close_file(FILE **fp){
    if(fp == NULL)
        return INVALID_NULL_POINTER;

    fclose(*fp);
    return SUCCESS;
}

void get_extention(const char *fileName, int size, char *outVector){
    for(int i = 1; i<=3; i++){
        outVector[i-1] = fileName[(size-4)+i];
    }
}

void get_image_proportions(const char *filename, int *nCols, int *nRows){

    char file_extention[3];
    get_extention(filename, strlen(filename), file_extention);

    FILE *fp;
    open_file(&fp, filename);

    // Se for arquivo.txt a obtenção dos dados de largura e altura será feito assim
    if(strcmp(file_extention, "txt") == 0){
        char pixelChar;
        int linha = 1, coluna = 1;
        while(!feof(fp)){
            fscanf(fp, "%c", &pixelChar);
            if(pixelChar == '\n')
                linha++;
            if(pixelChar == '\t')
                coluna++;
        }
        *nCols = (coluna/linha)+1;
        *nRows = linha;
        rewind(fp); // Retorna o ponteiro para o início do arquivo
    } 
    // Se for arquivo.imm a obtenção dos dados de largura e altura será feito assim 
    else if(strcmp(file_extention, "imm")==0){
        fread(nRows, sizeof(int), 1, fp);
        fread(nCols, sizeof(int), 1, fp);
    }

    close_file(&fp);
}

