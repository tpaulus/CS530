# Makefile for file parser


TORM = p1_driver p1_driver.o file_parser.o 
CC = g++
CCFLAGS = -g -O3 -Wall -Wpointer-arith -Wcast-qual -Wwrite-strings

driver:	p1_driver.o file_parser.o
	${CC} ${CCFLAGS} -o p1_driver p1_driver.o file_parser.o

p1_driver.o:	p1_driver.cpp
		${CC} ${CCFLAGS} -c p1_driver.cpp 

file_parser.o:	file_parser.cc file_parser.h file_parse_exception.h
		${CC} ${CCFLAGS} -c file_parser.cc

clean:
	rm -f ${TORM}
