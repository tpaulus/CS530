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
#include <utility>

#include "sicxe_asm.h"

using namespace std;

bool is_comment_or_empty(file_parser::formatted_line line);

sicxe_asm::sicxe_asm(string fn) {
    filename = fn;
    this->parser = new file_parser(fn);
    try {
        parser->read_file();
    } catch (file_parse_exception fileParseException) {
        cout << "ERROR - " << fileParseException.getMessage() << endl;
        exit(1);
    }
    symbol_table = new symtab();
    opcode_table = new opcodetab();
    listing_vector = new vector<file_parser::formatted_line>();
    forward_ref_vector = new vector<pair<file_parser::formatted_line, string> >;
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

void sicxe_asm::get_to_start_first_pass() {
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
    if(is_hex_string(line_iter->operand)){
        location_counter = hex_to_int(strip_hex_sign(line_iter->operand));
    } else {
        location_counter = dec_to_int(line_iter->operand);
    }
    line_iter++; //Gets to start (line following start)
}

void sicxe_asm::handle_assembler_directive() {
    string opcode = sicxe_asm::to_uppercase(line_iter->opcode);
    if (to_uppercase(line_iter->opcode) == "EQU") {
        if (line_iter->label.empty()) {
            cout << "ERROR - Expecting label for EQU assignment on line " << line_iter->linenum << endl;
            exit(4);
        } else if (symbol_table->contains(line_iter->label)) {
            cout << "ERROR - Duplicate label on line " << line_iter->linenum << endl;
            exit(4);
        } else {
            //Label is unique
            if(isalpha(*line_iter->operand.begin())){ //Is label
                if(symbol_table->contains(line_iter->operand)){
                    symbol_table->insert(line_iter->label, symbol_table->get_value(line_iter->operand), false);
                } else {
                    //Forward Reference
                    forward_ref_vector->push_back(pair<file_parser::formatted_line, string>(*line_iter, line_iter->operand));
                }
            } else { //Is Value
                if(is_hex_string(line_iter->operand)){
                    symbol_table->insert(line_iter->label, hex_to_int(strip_hex_sign(line_iter->operand)), false);
                } else {
                    symbol_table->insert(line_iter->label, dec_to_int(line_iter->operand), false);
                }
            }
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
        if (is_hex_string(line_iter->operand)) {
            location_counter += 3 * hex_to_int(strip_hex_sign(line_iter->operand));
        } else {
            location_counter += 3 * dec_to_int(line_iter->operand);
        }
    } else if (opcode == "RESB") {
        if (is_hex_string(line_iter->operand)) {
            location_counter += hex_to_int(strip_hex_sign(line_iter->operand));
        } else {
            location_counter += dec_to_int(line_iter->operand);
        }
    }

}

void sicxe_asm::handle_byte_directive() {
    size_t pos_left = (line_iter->operand).find_first_of('\''); //Left '
    size_t pos_right = (line_iter->operand).find_last_of('\''); //Right '
    string token = (line_iter->operand).substr(pos_left + 1, pos_right - pos_left - 1); //String between ' '

    if ((line_iter->operand).find('C') == 0 || (line_iter->operand).find('c') == 0) { //starts with C
        location_counter += token.length();
    } else if ((line_iter->operand).find('X') == 0 || (line_iter->operand).find('x') == 0) {  //starts with X
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

void sicxe_asm::set_forward_references() {
    vector<pair <file_parser::formatted_line, string> >::iterator fr_iter = forward_ref_vector->begin(); //Here to make for one one line // NOLINT
    for(; fr_iter != forward_ref_vector->end(); fr_iter++){
        string reference = fr_iter->second;
        if(symbol_table->contains(reference)){
            symbol_table->insert(fr_iter->first.label, symbol_table->get_value(reference), true);
        } else {
            //Forward Reference not found
            cout << "ERROR - Label \"" << reference << "\" on line " << fr_iter->first.linenum << " not found" << endl;
            exit(32);
        }
    }
}

void sicxe_asm::do_first_pass() {
    get_to_start_first_pass();
    // Start of flowchart loop
    while (line_iter != listing_vector->end() && sicxe_asm::to_uppercase(line_iter->opcode) != "END") {
        line_iter->address = sicxe_asm::int_to_hex(location_counter, 5);

        if (!is_assembler_directive(to_uppercase(line_iter->opcode)) && !is_comment_or_empty(*line_iter)) {
            if (!line_iter->label.empty()) {
                if (symbol_table->contains(line_iter->label)) {
                    cout << "ERROR - Duplicate label \"" << line_iter->label << "\" on line ";
                    cout << line_iter->linenum << endl;
                    exit(4);
                }
                symbol_table->insert(line_iter->label, location_counter, true);
            }

            if (!line_iter->opcode.empty()) {
                try {
                    if (opcode_table->is_valid(to_uppercase(line_iter->opcode))) {
                        location_counter += opcode_table->get_instruction_size(to_uppercase(line_iter->opcode));
                    }
                } catch (opcode_error_exception exception) {
                    cout << "ERROR - Invalid opcode \"" << line_iter->opcode << "\" on line ";
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
    set_forward_references();

}

// SECOND PASS FUNCTIONS

// Checks if offset is within -2048 and 2047 range
bool sicxe_asm::is_valid_pc(int offset) {
    return (offset <= 2047 && offset >= -2048);
}

// Checks if offset is within 0 and 2^12 (4096)
bool sicxe_asm::is_valid_base(int offset) {
    return (offset < 4096 && offset >= 0);
}

// Checks if value is within 0 and 2^20 (1048576)
bool sicxe_asm::is_valid_extended(int value) {
    return (value < 1048576 && value >= 0);
}

// Checks if the operand holds an immediate value
bool sicxe_asm::is_immediate(string operand) {
    return '#' == operand.at(0);
}

// Checks if the operand holds an indirect value
bool sicxe_asm::is_indirect(string operand) {
    return '@' == operand.at(0);
}

// Checks if the operand holds an indexed value
bool sicxe_asm::is_indexed(string operand) {
    // TODO: Any special cases???
                                                   //    , is at 5 here, length is 7
    return (operand.length() - 2) == operand.find(','); //alpha,x length starts at 1, find at 0
}

// Returns the register number for format two machine code
int sicxe_asm::get_register_number(string reg) {

    // TODO: Get the rest of the register values; 0 is a placeholder for now

    if(reg == "T")
        return 5;
    else if(reg == "S")
        return 4;
    else if(reg == "X")
        return 1;
    else if(reg == "A")
        return 0;
    else if(reg == "L")
        return 0;
    else if(reg == "B")
        return 0;
    else if(reg == "PC")
        return 0;
    else if(reg == "SW")
        return 0;
    else {
        cout << "ERROR - Invalid register in the operand \"" << reg << "\" on line ";
        cout << line_iter->linenum << endl;
        exit(11);
    }
}

int sicxe_asm::get_format(string opcode) {
    return opcode_table->get_instruction_size(std::move(opcode));
}

void sicxe_asm::handle_format_one() {
    line_iter->machinecode = hex_to_int(opcode_table->get_machine_code(line_iter->opcode));
}

void sicxe_asm::handle_format_three(){
    string opcode = to_uppercase(line_iter->opcode);
    if(is_indirect(opcode)){
        line_iter->machinecode |= SET_3N;

    } else if (is_immediate(opcode)){
        line_iter->machinecode |= SET_3I;

    } else if (is_indexed(opcode)){
        line_iter->machinecode |= SET_3X;
        line_iter->machinecode |= SET_3I;
        line_iter->machinecode |= SET_3N;
    } else {
        //No Addressing Mode
        line_iter->machinecode |= SET_3I;
        line_iter->machinecode |= SET_3N;

    }
}

void sicxe_asm::handle_format_four(){
    string opcode= to_uppercase(line_iter->opcode);
    string hex_machine_code = opcode_table->get_machine_code(opcode);
    int int_machine_code = hex_to_int(hex_machine_code);
    line_iter->machinecode= int_machine_code<<26;

    if(is_indirect(opcode)){
        line_iter->machinecode |= SET_4N;
        line_iter->machinecode |= SET_4E;


    } else if (is_immediate(opcode)){
        line_iter->machinecode |= SET_4I;
        line_iter->machinecode |= SET_4E;

    } else if (is_indexed(opcode)){
        line_iter->machinecode |= SET_4X;
        line_iter->machinecode |= SET_4I;
        line_iter->machinecode |= SET_4N;
        line_iter->machinecode |= SET_4E;


    } else {
        //No Addressing Mode
        line_iter->machinecode |= SET_4I;
        line_iter->machinecode |= SET_4N;
        line_iter->machinecode |= SET_4E;

    }

}

void sicxe_asm::do_second_pass() {
    line_iter = listing_vector->begin();
    while (to_uppercase(line_iter++->opcode) != "START") //Gets to line after start
    ; //Silences warning for no body while loop

        while (line_iter != listing_vector->end() && sicxe_asm::to_uppercase(line_iter->opcode) != "END") {
            if(line_iter->opcode.empty()){
                //Do Nothing
            } else if (is_assembler_directive(to_uppercase(line_iter->opcode))){
                //Handle Byte/Word Directives
            } else {
                // Check formats
                int format = get_format(line_iter->opcode);
                if (format == 1)
                    handle_format_one();
                else if (format == 2) {
                    // Handle format 2
                } else if (format == 3) {
                    handle_format_three();
                } else if (format == 4) {
                    handle_format_four();
                } else {
                    //TODO: Try/Catch in assemble() should handle this?
                    //  cout << "ERROR - Format type not detected on line ";
                    //cout << line_iter->linenum << endl;
                    //exit(12);
                }
            }
        line_iter++; //Grab next line and continue
    }

    //set_machinecode_after_end();
}

void sicxe_asm::write_listing_file() {
    string rawname = filename.substr(0, filename.length() - 4);
    ofstream lis_file((rawname + ".lis").c_str());

    //prog name
    long l = (filename).length() + 4;
    long pos = (50 - l) / 2;
    for (int i = 0; i < pos; i++)
        lis_file << " ";
    lis_file << "**" << filename << "**" << endl;

    //header
    lis_file << "Line#     ";
    lis_file << "Address     ";
    lis_file << "Label     ";
    lis_file <<  "Opcode     ";
    lis_file << "Operand     ";
    lis_file << "Machine Code     " << endl;
    lis_file << "=====     ";
    lis_file << "=======     ";
    lis_file << "=====     ";
    lis_file << "======     ";
    lis_file << "=======     ";
    lis_file << "============     " << endl;

    for (line_iter = listing_vector->begin(); line_iter != listing_vector->end(); line_iter++) {
        lis_file << *line_iter;
    }

    lis_file.close();
}

void sicxe_asm::assemble() {
    try {
        do_first_pass();
       // do_second_pass();
        write_listing_file();
    } catch (file_parse_exception error) {
        cout << "ERROR: " << error.getMessage() << endl;
        exit(9);
    } catch (opcode_error_exception error) {
        cout << "ERROR: On Line: " << line_iter->linenum << " " << error.getMessage() << endl;
        exit(8);
    } catch (symtab_exception error) {
        cout << "ERROR: " << error.getMessage() << endl;
        exit(7);
    } catch (exception error) {
      cout << "UNEXEPECTED ERROR: Something when wrong and we don't really know what." << endl;
      exit(1);
    }
}

bool sicxe_asm::is_assembler_directive(string opcode) {
    return (opcode == "NOBASE" || opcode == "BASE" || opcode == "RESB" || opcode == "RESW" || opcode == "WORD" ||
            opcode == "BYTE" || opcode == "EQU");
}

bool sicxe_asm::is_hex_string(string str) {
    return str.find('$') == 0;
}

string sicxe_asm::strip_hex_sign(string str) {
    return str.substr(1, str.size() - 1);
}

string sicxe_asm::hex_to_dec(string str) {
    return int_to_dec(hex_to_int(std::move(str)));
}

bool is_comment_or_empty(file_parser::formatted_line line) {
    return line.label.empty() && line.opcode.empty() && line.operand.empty();
}
