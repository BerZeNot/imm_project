#include "imm_resources.h"

int open(char const *filename){
    printf("Filename: %s\n", filename);
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