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

private:

    string filename;
    file_parser parser;
    vector<file_parser::formatted_line> list_vec;
    vector<file_parser::formatted_line>::iterator line_iter;
    string program_name;
    int location_counter;
    string BASE;


};



#endif //SICXE_ASM_H
