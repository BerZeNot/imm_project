#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TMat2D.h"
struct TMat2D
{
  int nrows; // número de linhas
  int ncolumns; // número de colunas
  double *data; // ponteiro para os dados da matriz
};

// mat = mat2D_create(4,3);

TMat2D *mat2D_create(int nrows, int ncolumns){
    TMat2D *mat;
    mat = malloc(sizeof(TMat2D));
    if (mat != NULL){
        mat->data = malloc(nrows*ncolumns*sizeof(double));
        if (mat->data != NULL){
            mat->ncolumns = ncolumns;
            mat->nrows = nrows;
        } else {
            free(mat);
            return NULL;
        }
    }
    return mat;
}

int mat2d_increase_size(TMat2D *mat, int nrows, int ncols){
    if(mat == NULL)
        return -1;
    if(nrows <= mat->nrows || ncols <= mat->ncolumns)
        return -1;

    double *dataTemp;
    dataTemp = malloc(nrows*ncols*sizeof(double));
    if(dataTemp==NULL)
        return -1;
    else{
        int pos;
        for(int i=0; i<nrows; i++){
            for(int j=0; j<ncols; j++){
                pos = j * nrows + i;
                
                if(i < mat->nrows && j < mat->ncolumns){
                    dataTemp[pos] = mat->data[pos];
                    printf("ADD -> i:%d | j:%d, valor: %lf\n", i, j, dataTemp[pos]);
                }
                else{
                    dataTemp[pos] = 0;
                    printf("IGNR -> i:%d | j:%d, valor: %lf\n", i, j, dataTemp[pos]);
                }
                // dataTemp[pos] = 6;
            }
        }
        mat->nrows = nrows; // refresh number of lines
        mat->ncolumns = ncols; // refresh number of columns
        free(mat->data); // free the memory alocated before
        mat->data = dataTemp; // set the new pointer
    }    
    return 0;
}
int mat2D_free(TMat2D *mat){
    if(mat == NULL){
        return -1;
    } else {
        free(mat->data);
        free(mat);
        return 0;
    }
}

int mat2D_set_value(TMat2D *mat, int i, int j, double val){
    if(mat == NULL)
        return -1;
    if(i >= mat->nrows || j >= mat->ncolumns)
        return -1;
    
    int pos;
    pos = j * mat->nrows + i;
    mat->data[pos] = val;
    return 0;
}

int mat2D_get_value(TMat2D *mat, int i, int j, double *val){

    if(mat == NULL)
        return -1;
    if(i >= mat->nrows || j >= mat->ncolumns)
        return -1;
    
    int pos;
    pos = j * mat->nrows + i;
    double valor;
    valor = mat->data[pos];
    *val = valor;
    return 0;
}

int mat2D_fill_with_random(TMat2D *mat, double minValue, double maxValue){
    if(mat == NULL)
        return -1;
    if(minValue > maxValue)
        return -1;
    
    srand(time(NULL));
    for(int i=0; i < (mat->ncolumns*mat->nrows); i++){
        double randNum;
        do{
            randNum = (rand()/(double)RAND_MAX)*maxValue;
        } while(randNum<minValue);
        mat->data[i] = randNum;
    }
    return 0;
}

int mat2D_sum_two_matrix(TMat2D *mat1, TMat2D *mat2, TMat2D *matResult){
    if(mat1 == NULL || mat2 == NULL || matResult == NULL)
        return -1;
    
    if(mat1->ncolumns != mat2->ncolumns || mat1->nrows != mat2->nrows)
        return -1;
    
    if(mat1->nrows != matResult->nrows || mat1->ncolumns != matResult->ncolumns)
        return -1;
    
    for(int i = 0; i < (matResult->nrows*matResult->ncolumns); i++){
        matResult->data[i] = mat1->data[i] + mat2->data[i];
    }
    return 0;
}

int mat2D_multiply_mat_scalar(TMat2D *mat1, TMat2D *matResult, double scalar){
    if(mat1 == NULL || matResult == NULL)
        return -1;
    
    if(mat1->nrows != matResult->nrows || mat1->ncolumns != matResult->ncolumns)
        return -1;

    for(int i=0; i<(mat1->ncolumns*mat1->ncolumns); i++){
        matResult->data[i] = mat1->data[i] * scalar;
    }
    return 0;

}

int mat2D_sum_lines(TMat2D *mat, double *vector){
    if(mat == NULL)
        return -1;
    else {
        double tempSum;
        int pos;
        for(int i=0; i < mat->nrows; i++){
            for(int j=0; j < mat->ncolumns; j++){
                pos = j * mat->nrows + i;
                tempSum += mat->data[pos];
            }
            vector[i] = tempSum;
            tempSum = 0;
        }
        return 0;
    }
}

int mat2D_calculate_trace(TMat2D *mat1, double *result){
    if(mat1 == NULL)
        return -1;
    
    if(mat1->ncolumns != mat1->nrows)
        return -1;
    int pos;
    double soma=0;
    for(int i=0; i<mat1->nrows; i++){
        for(int j=0; j<mat1->ncolumns; j++){
            if(i==j){
                pos = j * mat1->nrows + i;
                soma += mat1->data[pos];
            }
        }
    }
    *result = soma;
    return 0;
}

int mat2D_get_number_of_rows(TMat2D *mat, int *result){
    if(mat == NULL)
        return -1;
    else {
        *result = mat->nrows;
        return 0;
    }
}

int mat2D_get_number_of_columns(TMat2D *mat, int *result){
    if(mat == NULL)
        return -1;
    else {
        *result = mat->ncolumns;
    }
}

int mat2D_print_matrix(TMat2D *mat){
    if(mat == NULL)
        return -1;

    for(int i=0; i<mat->nrows; i++){
        for(int j=0; j<mat->ncolumns; j++){
            int pos = j * mat->nrows + i;
            printf("[%lf] ",mat->data[pos]);
        }
        printf("\n");
    }
}