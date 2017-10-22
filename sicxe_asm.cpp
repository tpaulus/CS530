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
    stirng getmachinecode() const;
    
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

string listing_line::getaddress() const {
    return address;
}

unsigned int listing_line::getlinenum() const {
    return linenum;
}

string listing_line::getlabel() const {
    return label;
}

string listing_line::getopcode() const {
    return opcode;
}

string listing_line::getoperand() const {
    return operand;
}

string listing_line::getmachinecode() const {
    return machinecode;
}

int main(int argc, char *argv[]) {
    string filename = argv[1];

}

