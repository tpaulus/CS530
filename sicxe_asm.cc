/*
 * Alexander Pearson-Goulart, Athena Campbell, Jon Verne, Neha Nene, Tom Paulus, William Fox
 * cssc1015
 * Team Virginia
 * prog3
 * CS530, Fall 2017
 *
*/
#include <string>
#include <iostream>
#include <iomanip>

#include "file_parser.cc"
#include "sicxe_asm.h"
#include "opcodetab.cc"

using namespace std;

int main(int argc, char *argv[]) {
    string filename = argv[1];
    try {
    file_parser parser(filename);
    parser.read_file();
    parser.print_file();
    }
    catch(file_parse_exception excpt) {
        cout << "**Sorry, error " << excpt.getMessage() << endl;
    }

    opcodetab opcode_list;
}

