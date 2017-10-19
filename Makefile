#make file for prog3, CS530 Fall 2017

TORM = opcodetab.o sicxe_asm sicxe_asm.o file_parser.o symtab.o
CC = g++
CCFLAGS = -g -O3 -Wall -Wpointer-arith -Wcast-qual -Wwrite-strings 

sicxe_asm:	sicxe_asm.o 
	${CC} ${CCFLAGS} -o sicxe_asm sicxe_asm.o opcodetab.o file_parser.o symtab.o

sicxe_asm.o:	sicxe_asm.cpp sicxe_asm.h opcodetab.o file_parser.o symtab.o 
		${CC} ${CCFLAGS} -c sicxe_asm.cpp
            
opcodetab.o:	opcodetab.cc opcodetab.h opcode_error_exception.h
			${CC} ${CCFLAGS} -c opcodetab.cc                    


symtab.o:	symtab.cc symtab.h symtab_exception.h
		${CC} ${CCFLAGS} -c symtab.cc  
  
file_parser.o:	file_parser.cc file_parser.h file_parse_exception.h
		${CC} ${CCFLAGS} -c file_parser.cc                
clean:
	rm -f ${TORM}
