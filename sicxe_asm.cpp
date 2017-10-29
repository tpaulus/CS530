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
#include <stdlib.h>

#include "sicxe_asm.h"
using namespace std;

bool is_comment_or_empty(file_parser::formatted_line line);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Error, you must supply the name of the file to assemble." << endl;
        exit(1);
    }
    string filename = argv[1];  //TODO: Need to check if this exists
    file_parser parser(filename);
    parser.read_file();
    vector <file_parser::formatted_line> listing_vector(100);
    //Loads new Vector of Structs
    for(unsigned int i = 0; i < parser.size(); i++) {
        listing_vector.push_back(parser.get_struct(i));
    }

}

bool is_comment_or_empty(file_parser::formatted_line line) {
    return line.label.empty() && line.opcode.empty() && line.operand.empty();
}
