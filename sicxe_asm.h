/*
 * Alexander Pearson-Goulart, Athena Campbell, Jon Verne, Neha Nene, Tom Paulus, William Fox
 * cssc1015
 * Team Virginia
 * prog3
 * CS530, Fall 2017
 *
*/

#ifndef SICXE_ASM_H
#define SICXE_ASM_H

#include <string>
#include <vector>
#include <cstdio>
#include <sstream>
#include <algorithm>

#include "file_parser.h"
#include "file_parse_exception.h"
#include "opcodetab.h"
#include "opcode_error_exception.h"
#include "symtab.h"
#include "symtab_exception.h"


using namespace std;

class sicxe_asm {

public:

    sicxe_asm(string);

    void assemble();

    inline static int string_to_int(string s){
        istringstream instr(s);
        int n;
        instr >> n;
        return n;
    }

    inline static int hex_to_int(string s){
        int value;
        sscanf(s.c_str(), "%x", &value);
        return value;
    }

    inline static int dec_to_int(string s){
        int value;
        sscanf(s.c_str(), "%d", &value);
        return value;
    }

    inline static string to_uppercase(string s){
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        return s;
    }
    inline static string int_to_hex(int num, int width){
        stringstream out;
        out << setw(width) << setfill('0') << hex << num;
        return to_uppercase(out.str());
    }

    inline static string int_to_dec(int num){
        stringstream out;
        out << dec << num;
        return out.str();
    }

private:

    string filename;
    file_parser *parser;
    symtab *symbol_table;
    opcodetab *opcode_table;
    vector<file_parser::formatted_line> *listing_vector;
    vector<file_parser::formatted_line>::iterator line_iter;

    string program_name;
    string BASE;
    int location_counter;

    void load_vector();
    void do_first_pass();
    void get_to_start();
    void handle_assembler_directive();
    void handle_byte_directive();
    void set_addresses_after_end();

    void do_second_pass();

    void write_listing_file();

    bool is_assembler_directive(string);
};

inline std::ofstream &operator<<(std::ofstream &out, const file_parser::formatted_line &f_l) {
    const int linenum_col_width =5;
    const int address_col_width = 7;
    const int label_col_width = 5;
    const int opcode_col_width = 6;

    out << std::setw(linenum_col_width) << std::right << std::setfill(' ') <<f_l.linenum<<"  ";
    out << std::setw(address_col_width) << std::right << std::setfill(' ') <<f_l.address<< "  ";
    out << std::setw(label_col_width) << std::left << std::setfill(' ') <<f_l.label<<"  ";
    out << std::setw(opcode_col_width) << std::left << std::setfill(' ') << f_l.opcode<<"  ";
    out << f_l.operand << std::endl;

    return out;
}


#endif //SICXE_ASM_H
