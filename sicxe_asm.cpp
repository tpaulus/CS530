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

sicxe_asm::sicxe_asm(string fn) {
    filename = fn;
    this->parser = new file_parser(fn);// = new file_parser(fn);
    try {
        parser->read_file();
       file_parser::formatted_line name = parser->get_struct(0);
    } catch (file_parse_exception fileParseException) {
        cout << "ERROR - " << fileParseException.getMessage() << endl;
        exit(1);
    }
    symtab symbol_table;
    opcodetab opcode_table;
    vector<file_parser::formatted_line> listing_vector;
    vector<file_parser::formatted_line>::iterator line_iter;
    string program_name = "";
    string BASE = "";
    int location_counter = 0;
    for (int i = 0; i < parser->size(); i++) {
        this->listing_vector.push_back(parser->get_struct((unsigned int) i));
    }
}

void sicxe_asm::load_vector() {
    for (int i = 0; i < parser->size(); i++) {
        listing_vector.push_back(parser->get_struct((unsigned int) i));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Error, you must supply the name of the file to assemble." << endl;
        exit(1);
    }
    string filename = argv[1];

    sicxe_asm *assembler = new sicxe_asm(filename);
    assembler->assemble();

}

void sicxe_asm::get_to_start() {
    line_iter = listing_vector.begin(); //Grabs first line
    //While more lines and operand != start
    while (line_iter != listing_vector.end() && sicxe_asm::to_uppercase(line_iter->opcode) != "START") {
        if (!is_comment_or_empty(*line_iter)) {
            cout << "ERROR - No executable code before START Directive: Line " << line_iter->linenum << endl;
            cout << *line_iter << endl;
            exit(2);
        }
        line_iter++; //Grab next line
    }
    if (line_iter == listing_vector.end()) {
        cout << "ERROR - No START Directive" << endl; //We can't know the line number, following the iterator is nullptr
        exit(3);
    }
    //Get Program name and starting location counter
    program_name = line_iter->label;
    location_counter = sicxe_asm::hex_to_int(line_iter->operand);
    line_iter++;
}



void sicxe_asm::do_first_pass() {
    get_to_start();
    //loop_through_lines(); //In here implement flowchart


    //TODO: This is now where start is in the flowchart

    //starts part D
    if (false) {

    } else {
        if (line_iter->label != "") {
            if (symbol_table.contains(line_iter->label)) {
                cout << "ERROR - Duplicate label on line " << line_iter->linenum << endl;
                exit(4);
            }
            symbol_table.insert(line_iter->label, sicxe_asm::int_to_dec(location_counter), true);
        }
        string opcode = sicxe_asm::to_uppercase(line_iter->opcode);
        if (opcode == "BASE")
            BASE = (line_iter->operand);
        else if (opcode == "NOBASE")
            BASE = "";
        else if (opcode == "WORD")
            location_counter += 3;
        else if (opcode == "BYTE") {


            size_t pos_left = (line_iter->operand).find_first_of("'"); //Left '
            size_t pos_right = (line_iter->operand).find_last_of("'"); //Right '
            string token = (line_iter->operand).substr(pos_left + 1, pos_right - pos_left - 1); //String between ' '

            if ((line_iter->operand).find("C") == 0) //starts with C
                location_counter++;
            else if ((line_iter->operand).find("X") == 0) {  //starts with X
                if ((((int) token.length()) & 1) == 1) {
                    cout << "ERROR - Invalid operand for BYTE on line " << line_iter->linenum << endl;
                    exit(6);
                }
                location_counter += (((int) token.length()) >> 1);
            } else {
                cout << "ERROR - Invalid operand for BYTE on line " << line_iter->linenum << endl;
                exit(7);
            }
        } else if (opcode == "RESW") {
            location_counter += 3 * sicxe_asm::dec_to_int(line_iter->operand);
        } else if (opcode == "RESB") {
            location_counter += sicxe_asm::dec_to_int(line_iter->operand);
        }
        line_iter->address = sicxe_asm::int_to_hex(location_counter, 5);
    }

}

void sicxe_asm::do_second_pass() {
// TODO: in Prog 4
}

void sicxe_asm::assemble() {

    do_first_pass();
    //do_second_pass();

}

bool is_comment_or_empty(file_parser::formatted_line line) {
    return line.label.empty() && line.opcode.empty() && line.operand.empty();
}

