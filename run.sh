gcc -c imm.c -o imm.o
gcc -c imm_resources.c -o imm_resources.o
gcc -c TMat2D.c -o TMat2D.o
gcc -o imm  imm.o imm_resources.o imm_resources.h TMat2D.o TMat2D.h