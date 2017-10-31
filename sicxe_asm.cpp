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
#include <iostream>
#include <fstream>


#include "sicxe_asm.h"

using namespace std;

bool is_comment_or_empty(file_parser::formatted_line line);

sicxe_asm::sicxe_asm(string fn) {
    filename = fn;
    this->parser = new file_parser(fn);// = new file_parser(fn);
    try {
        parser->read_file();
    } catch (file_parse_exception fileParseException) {
        cout << "ERROR - " << fileParseException.getMessage() << endl;
        exit(1);
    }
    symbol_table = new symtab();
    opcode_table = new opcodetab();
    listing_vector = new vector<file_parser::formatted_line>();
    program_name = "";
    BASE = "";
    location_counter = 0;
    load_vector();
    line_iter = listing_vector->begin();
}

void sicxe_asm::load_vector() {
    for (int i = 0; i < parser->size(); i++) {
        listing_vector->push_back(parser->get_struct((unsigned int) i));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "ERROR - Name of the file to assemble must be provided." << endl;
        exit(1);
    }
    string filename = argv[1];

    sicxe_asm *assembler = new sicxe_asm(filename);
    assembler->assemble();

}

void sicxe_asm::get_to_start() {
    line_iter = listing_vector->begin(); //Grabs first line
    //While more lines and operand != start
    while (line_iter != listing_vector->end() && sicxe_asm::to_uppercase(line_iter->opcode) != "START") {
        if (!is_comment_or_empty(*line_iter)) {
            cout << "ERROR - No executable code allowed before START Directive on line " << line_iter->linenum << endl;
            exit(2);
        }
        line_iter->address = int_to_hex(location_counter, 5); //Load 000000 into address field (cosmetic)
        line_iter++; //Grab next line
    }
    if (line_iter == listing_vector->end()) {
        cout << "ERROR - No START Directive" << endl; //We can't know the line number, following the iterator is nullptr
        exit(3);
    }
    //Set Program name
    program_name = line_iter->label;
    //Load 000000 into address field (cosmetic) for line with START directive
    line_iter->address = line_iter->address = int_to_hex(location_counter, 5);
    //Loads start address to location counter
    //TODO: Check to see if will always be hex (this assumes always hex)
    location_counter = sicxe_asm::hex_to_int(line_iter->operand);
    line_iter++; //Gets to start (line following start)
}

void sicxe_asm::handle_assembler_directive() {
    string opcode = sicxe_asm::to_uppercase(line_iter->opcode);
    if (to_uppercase(line_iter->opcode) == "EQU") {
        if (line_iter->label == "") {
            cout << "ERROR - Expecting label for EQU assignment on line " << line_iter->linenum << endl;
            exit(4);
        } else if (symbol_table->contains(line_iter->label)) {
            cout << "ERROR - Duplicate label on line " << line_iter->linenum << endl;
            exit(4);
        } else {
            //Label is unique
            // TODO: value or label
            symbol_table->insert(line_iter->label, line_iter->operand, true);
        }
    } else if (opcode == "BASE") {
        BASE = (line_iter->operand);
    } else if (opcode == "NOBASE") {
        BASE = "";
    } else if (opcode == "WORD") {
        location_counter += 3;
    } else if (opcode == "BYTE") {
        handle_byte_directive();
    } else if (opcode == "RESW") {
        location_counter += 3 * dec_to_int(line_iter->operand);
    } else if (opcode == "RESB") {
        location_counter += dec_to_int(line_iter->operand);
    }

}

void sicxe_asm::handle_byte_directive() {
    size_t pos_left = (line_iter->operand).find_first_of("'"); //Left '
    size_t pos_right = (line_iter->operand).find_last_of("'"); //Right '
    string token = (line_iter->operand).substr(pos_left + 1, pos_right - pos_left - 1); //String between ' '

    if ((line_iter->operand).find("C") == 0 || (line_iter->operand).find("c") == 0) { //starts with C
        location_counter += token.length();
    } else if ((line_iter->operand).find("X") == 0 || (line_iter->operand).find("x") == 0) {  //starts with X
        if ((((int) token.length()) & 1) == 1) {
            cout << "ERROR - Invalid operand " << line_iter->operand << " for BYTE on line ";
            cout << line_iter->linenum << endl;
            exit(7);
        }
        location_counter += (((int) token.length()) >> 1);
    } else {
        //Doesn't start with C or X
        cout << "ERROR - Invalid operand " << line_iter->operand;
        cout << " for BYTE on line " << line_iter->linenum << endl;
        exit(7);
    }
}

void sicxe_asm::set_addresses_after_end() {
    for (; line_iter != listing_vector->end(); line_iter++) {
        line_iter->address = int_to_hex(location_counter, 5);
    }
}

void sicxe_asm::do_first_pass() {
    get_to_start();
    // Start of flowchart loop
    while (line_iter != listing_vector->end() && sicxe_asm::to_uppercase(line_iter->opcode) != "END") {
        line_iter->address = sicxe_asm::int_to_hex(location_counter, 5);

        if (!is_assembler_directive(to_uppercase(line_iter->opcode)) && !is_comment_or_empty(*line_iter)) {
            if (line_iter->label != "") {
                if (symbol_table->contains(line_iter->label)) {
                    cout << "ERROR - Duplicate label \""<< line_iter->label << "\" on line ";
                    cout << line_iter->linenum << endl;
                    exit(4);
                }
                symbol_table->insert(line_iter->label, int_to_hex(location_counter, 5), true);
            }

            if (line_iter->opcode != "") {
                try {
                    if (opcode_table->is_valid(to_uppercase(line_iter->opcode))) {
                        location_counter += opcode_table->get_instruction_size(to_uppercase(line_iter->opcode));
                    }
                } catch (opcode_error_exception exception) {
                    cout << "ERROR - Invalid opcode \""<< line_iter->opcode << "\" on line ";
                    cout << line_iter->linenum << endl;
                    exit(10);
                }
            }

        } else {
            handle_assembler_directive();
        }
        line_iter++; //Grab next line and continue
    }

    set_addresses_after_end();

    //Prints basics of listing file for error checking
//    for (line_iter = listing_vector->begin(); line_iter != listing_vector->end(); line_iter++) {
//        cout << line_iter->linenum << "        " << hex_to_int(line_iter->address) << "        " << line_iter->opcode
//             << "        " << line_iter->operand << endl;
//    }
//    cout << "*********" << endl;

   // cout << symbol_table->get_value("OFFB") << endl; //Checks EQU assignment in source3.asm

}

void sicxe_asm::do_second_pass() {
// TODO: in Prog 4
}

void sicxe_asm::write_listing_file() {
    //TODO:
    ofstream lis_file;
    size_t extension = filename.find_last_of(".");
    string rawname = filename.substr(0,extension);
    lis_file.open(rawname+".lis");

    //header
    lis_file << std::setw(5) << std::left << std::setfill(' ') <<"Line#  ";
    lis_file << std::setw(7) << std::left << std::setfill(' ') <<"Address  ";
    lis_file << std::setw(5) << std::left << std::setfill(' ') <<"Label  ";
    lis_file << std::setw(6) << std::left << std::setfill(' ') << "Opcode  ";
    lis_file << "Operand" << std::endl;
    lis_file << std::setw(5) << std::left << std::setfill(' ') <<"=====  ";
    lis_file << std::setw(7) << std::left << std::setfill(' ') <<"=======  ";
    lis_file << std::setw(5) << std::left << std::setfill(' ') <<"=====  ";
    lis_file << std::setw(6) << std::left << std::setfill(' ') << "======  ";
    lis_file << "=======" << std::endl;

    for (line_iter = listing_vector->begin(); line_iter != listing_vector->end(); line_iter++) {
        lis_file << *line_iter;

    }
    lis_file.close();

}

void sicxe_asm::assemble() {
    try {
        do_first_pass();
        //do_second_pass();
        write_listing_file();
    } catch (file_parse_exception error) {
        cout << "ERROR: " << error.getMessage() << endl;
        exit(9);
    } catch (opcode_error_exception error) {
        cout << "ERROR: " << error.getMessage() << endl;
        exit(8);
    } catch (symtab_exception error) {
        cout << "ERROR: " << error.getMessage() << endl;
        exit(7);
    }
}

bool sicxe_asm::is_assembler_directive(string opcode) {
    return (opcode == "NOBASE" || opcode == "BASE" || opcode == "RESB" || opcode == "RESW" || opcode == "WORD" ||
            opcode == "BYTE" || opcode == "EQU");
}

bool is_comment_or_empty(file_parser::formatted_line line) {
    return line.label.empty() && line.opcode.empty() && line.operand.empty();
}
