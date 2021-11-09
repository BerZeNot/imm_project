#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define CANT_CREATE_IMAGE -2
#define CANT_OPEN_FILE -3
#define UNSUPPORTED_FILE_FORMAT -4
#define MISSING_FILENAME -5
#define INVALID_THR_VALUE -6


typedef struct TImage TImage; 

// FUNÇÕES DO TAD
// Aloca memória para uma imagem 
TImage *image_create(int nrows, int ncolumns);

// Libera a memória alocada para uma imagem
int image_free(TImage *image);

// Imprime a imagem carregada no TAD Image
int image_print(TImage *image);

// Carrega os dados de um arquivo para uma imagem
int image_load_data(TImage *image, const char *filename);

// Faz o threshold da imagem
int image_threshold(TImage *image, int thr);

int image_connected_component(TImage *image, TImage *imageRot);

// Inicializa a imagem com valor 0 em todos os pixels
int image_initialize(TImage *image);

// Abre um arquivo de texto ou binário de acordo com a extenção (.txt ou .imm)
int open_file(FILE **fp, const char *filename);

// Escreve os dados da imagem em um arquivo de saída
int write_file(TImage *image, const char *outfile_name);

// Fecha um arquivo
int close_file(FILE **fp);

// Obtem a extensão do arquivo
void get_extention(const char *fileName, int size, char *outVector);

// Obtem o número de colunas e linhas da imagem
void get_image_proportions(const char *filename, int *nCols, int *nRows);

