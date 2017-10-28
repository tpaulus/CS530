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

#include "sicxe_asm.h"

using namespace std;

struct listing_line {
    string address;
    unsigned int linenum;
    string label;
    string opcode;
    string operand;
    string machinecode;

    string getaddress() const;
    unsigned int getlinenum() const;
    string getlabel() const;
    string getopcode() const;
    string getoperand() const;
    string getmachinecode() const;

    listing_line(void){
        address="";
        linenum=0; //TODO check if 0 is the correct initializer in C++
        label="";
        opcode="";
        operand="";
        machinecode="";
    }
    ~listing_line(){
    }

};

string sicxe_asm::listing_line::getaddress() const {
    return address;
}

unsigned int sicxe_asm::listing_line::getlinenum() const {
    return linenum;
}

string sicxe_asm::listing_line::getlabel() const {
    return label;
}

string sicxe_asm::listing_line::getopcode() const {
    return opcode;
}

string sicxe_asm::listing_line::getoperand() const {
    return operand;
}

string sicxe_asm::listing_line::getmachinecode() const {
    return machinecode;
}

bool skip_check(listing_line line);

int main(int argc, char *argv[]) {

    string filename = argv[1];  //TODO: Need to check if this exists
    file_parser parser(filename);
    parser.read_file();

    vector <listing_line> list_vec(100);
    listing_line tmp_line;


    for(unsigned int i = 0; i < parser.size(); i++) {

        tmp_line.linenum = i + 1; //Source files are one based
        tmp_line.label = parser.get_token(i,0);
        tmp_line.opcode = parser.get_token(i,1);
        tmp_line.operand = parser.get_token(i,2);
        if(skip_check(tmp_line))
            continue;
        list_vec.push_back(tmp_line);
    }

}

bool skip_check(listing_line line) {
    return line.label.empty() && line.opcode.empty() && line.operand.empty();
}
