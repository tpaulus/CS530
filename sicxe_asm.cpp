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
    string filename = argv[1];

    file_parser parser(filename);
    try{
        parser.read_file();
    }catch (file_parse_exception fileParseException){
        cout << "ERROR - " << fileParseException.getMessage() << endl;
        exit(1);
    }
    vector <file_parser::formatted_line> listing_vector(0);
    vector<file_parser::formatted_line>::iterator line_iter;
    //Loads new Vector of Structs
    for(int i = 0; i < parser.size(); i++) {
        listing_vector.push_back(parser.get_struct((unsigned int)i));
    }

    line_iter = listing_vector.begin(); //Grabs first line
    //While more lines and operand != start
    while(line_iter != listing_vector.end() && sicxe_asm::to_uppercase(line_iter->opcode) != "START"){
        if(!is_comment_or_empty(*line_iter)){
            cout << "ERROR - No executable code before START Directive: Line " << line_iter->linenum << endl;
            cout << *line_iter << endl;
            exit(2);
        }
        line_iter++; //Grab next line
    }
    if(line_iter == listing_vector.end()){
        cout << "ERROR - No START Directive" << endl; //We can't know the line number, following the iterator is nullptr
        exit(3);
    }
    //Get Program name and starting location counter
    string program_name = line_iter->label;
    int location_counter = sicxe_asm::hex_to_int(line_iter->operand);
    //TODO: This is now where start is in the flowchart
    

}

bool is_comment_or_empty(file_parser::formatted_line line) {
    return line.label.empty() && line.opcode.empty() && line.operand.empty();
}

