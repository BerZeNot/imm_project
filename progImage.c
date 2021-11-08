#include <stdio.h>
#include "TImage.h"

int main(int argc, char const *argv[])
{
    TImage *image;
    
    int nRows=0, nCols=0;
    FILE *fp;
    
    open_file(&fp, argv[1]);
    
    get_image_proportions(argv[1],&nCols, &nRows);
    printf("Ncols: %d, Nrows: %d\n", nCols, nRows);
    image = image_create(nRows,nCols);
    if(image == NULL)
        printf("Can't create image!\n");
    else
        printf("Image created sucessful!\n");
    
    printf("Entrou no loadData\n");
    image_load_data(image, argv[1]);
    printf("Saiu do loadData\n");
    image_print(image);
    image_free(image);

    return 0;
}
