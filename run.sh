gcc -c TImage.c -o TImage.o

gcc -c imm_resources.c -o imm_resources.o

gcc -c imm.c -o imm.o

gcc -o imm imm.o TImage.o TImage.h imm_resources.o imm_resources.h