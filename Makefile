# Makefile for Opcode


TORM = driver driver.o opcodetab.o
CC = g++
CCFLAGS = -g -O3 -Wall -Wpointer-arith -Wcast-qual -Wwrite-strings

driver:	driver.o opcodetab.o
	${CC} ${CCFLAGS} -o driver driver.o opcodetab.o

p1_driver.o:	opcodetab.cpp
		${CC} ${CCFLAGS} -c opcodetab.cpp

file_parser.o:	opcodetab.cc opcodetab.h opcode_error_exception.h
		${CC} ${CCFLAGS} -c opcodetab.cc

clean:
	rm -f ${TORM}
