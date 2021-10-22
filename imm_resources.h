#include <stdio.h>

#define SUCCESS 0

int open(char const *filename);

int convert(char const *filename, char const *outfile_name);

int segment(char const *filename, char const *outfile_name);

int connected_component(char const *filename, char const *outfile_name);

int lab(char const *filename, char const *outfile_name);

void help();