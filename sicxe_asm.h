/*
 * Alexander Pearson-Goulart, Athena Campbell, Jon Verne, Neha Nene, Tom Paulus, William Fox
 * cssc1015
 * Team Virginia
 * prog4
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

// Defines for bit setting NIXBPE format 3
#define SET_3N 0x20000
#define SET_3I 0x10000
#define SET_3X 0x08000
#define SET_3B 0x04000
#define SET_3P 0x02000

// Defines for bit setting NIXBPE format 4
#define SET_4N (SET_3N << 8)
#define SET_4I (SET_3I << 8)
#define SET_4X (SET_3X << 8)
#define SET_4E 0x100000

using namespace std;

class sicxe_asm {

public:

    explicit sicxe_asm(string);

    void assemble();

    inline static int string_to_int(string s) {
        istringstream instr(s);
        int n;
        instr >> n;
        return n;
    }

    inline static int hex_to_int(string s) {
        int value;
        sscanf(s.c_str(), "%x", &value);
        return value;
    }

    inline static int dec_to_int(string s) {
        int value;
        sscanf(s.c_str(), "%d", &value);
        return value;
    }

    inline static string to_uppercase(string s) {
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        return s;
    }

    inline static string int_to_hex(int num, int width) {
        stringstream out;
        out << setw(width) << setfill('0') << hex << num;
        return to_uppercase(out.str());
    }

    inline static string int_to_dec(int num) {
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

    vector<pair<file_parser::formatted_line, string> > *forward_ref_vector;

    string program_name;
    string BASE;
    int location_counter;

    void load_vector();
    void do_first_pass();

// First Pass Procedures
    void get_to_start_first_pass();
    void handle_assembler_directive();
    void handle_byte_directive();
    void set_addresses_after_end();
    void set_forward_references();



// Second Pass Procedures
    void do_second_pass();
    bool is_valid_pc(int);
    bool is_valid_base(int);
    bool is_valid_extended(int);
    bool is_immediate(string);
    bool is_indirect(string);
    bool is_indexed(string);
    int get_register_number(string);
    int get_format(string);

    void handle_format_one();
    void handle_format_two();
    void handle_format_three();
    void handle_format_four();

    void format_machinecode(int);

// Functions

    void write_listing_file();
    
    string strip_flag(string);
    bool is_assembler_directive(string);
    bool is_hex_string(string);
    string hex_to_dec(string);
    
    string string_to_ascii(string);
    void handle_byte();
    void handle_word();
};

inline std::ofstream &operator<<(std::ofstream &out, const file_parser::formatted_line &f_l) {
    const int linenum_col_width = 5;
    const int address_col_width = 7;
    const int label_col_width = 10;
    const int opcode_col_width = 11;
    const int operand_col_width = 12;

    out << std::setw(linenum_col_width) << std::right << std::setfill(' ') << f_l.linenum << "     ";
    out << std::setw(address_col_width) << std::right << std::setfill(' ') << f_l.address << "     ";
    out << std::setw(label_col_width) << std::left << std::setfill(' ') << f_l.label;
    out << std::setw(opcode_col_width) << std::left << std::setfill(' ') << f_l.opcode;
    out << std::setw(operand_col_width) << std::left << std::setfill(' ') << f_l.operand;
    out << f_l.formatted_machinecode << std::endl;

    return out;
}


#endif //SICXE_ASM_H
