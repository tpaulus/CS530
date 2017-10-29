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

#include "file_parser.h"
#include "file_parse_exception.h"
#include "opcodetab.h"
#include "opcode_error_exception.h"
#include "symtab.h"
#include "symtab_exception.h"

using namespace std;

class sicxe_asm {

public:

private:

    struct listing_line{
        string address;
        unsigned int linenum;
        string label;
        string opcode;
        string operand;
        string machinecode;
        
        inline listing_line(){
        address="";
        linenum=0; 
        label="";
        opcode="";
        operand="";
        machinecode="";
        }
            
        std::string getaddress() const;
        unsigned int getlinenum() const;
        std::string getlabel() const;
        std::string getopcode() const;
        std::string getoperand() const;
        std::string getmachinecode() const;
        
    };
    string filename;
    file_parser parser;
    vector<listing_line> list_vec;
    listing_line tmp_line;

};



#endif //SICXE_ASM_H
