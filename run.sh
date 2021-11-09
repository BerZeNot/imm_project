gcc -c TImage.c -o TImage.o

gcc -c imm_resources.c -o imm_resources.o

gcc -c imm.c -o imm.o

gcc -c TStackPoint.c -o TStackPoint.o

gcc -o imm imm.o TImage.o TImage.h TStackPoint.o TStackPoint.h imm_resources.o imm_resources.h
