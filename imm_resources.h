// #include "TImage.h"

int open(const char *filename);

int convert(char const *filename, char const *outfile_name);

int segment(char const *thr, char const *filename, char const *outfile_name);

int connected_component(char const *filename, char const *outfile_name);

int lab(char const *filename, char const *outfile_name);

void getExtention(const char *fileName, int size, char *outVector);

void help();