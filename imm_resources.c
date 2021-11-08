#include "TImage.h"

int open(const char *filename){
    TImage *image;

    int nRows=0, nCols=0;
   
    FILE *fp;
    
    open_file(&fp, filename);
    
    get_image_proportions(filename ,&nCols, &nRows);
    
    image = image_create(nRows,nCols);
    
    if(image == NULL){
        printf("Can't create image!\n");
        return CANT_CREATE_IMAGE;
    }

    image_load_data(image, filename);
    image_print(image);
    image_free(image);

    return SUCCESS;
}

int convert(char const *filename, char const *outfile_name){
    TImage *image;

    int nRows=0, nCols=0;
   
    FILE *fp;
    
    open_file(&fp, filename);
    
    get_image_proportions(filename, &nCols, &nRows);
    
    image = image_create(nRows,nCols);
    
    if(image == NULL)
        printf("Can't create image!\n");

    image_load_data(image, filename);
    
    write_file(image, outfile_name);
    
    image_free(image);

    return SUCCESS;
}

int segment(char const *thr, char const *filename, char const *outfile_name){
    printf("segment\n");
    return 0;
}

int connected_component(char const *filename, char const *outfile_name){
    printf("connected_component\n");
    return 0;
}

int lab(char const *filename, char const *outfile_name){
    printf("connected_component\n");
    return 0;
}

void help(){
    printf("<< Possible commands >>\n");
    printf("-open (./imm -open filename.txt) \n");
    printf("-convert (./imm -convert filename.txt outfilename.imm)\n");
    printf("-segment (./imm -segment filename.txt outfilename.imm)\n");
    printf("-cc (./imm -cc filename.txt outfilename.imm)\n");
    printf("-lab (./imm -lab filename.txt outfilename.imm)\n");
}