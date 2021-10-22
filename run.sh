gcc -c imm.c -o imm.o
gcc -c imm_resources.c -o imm_resources.o
gcc -o imm  imm.o imm_resources.o imm_resources.h