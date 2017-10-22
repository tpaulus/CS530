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

using namespace std;

class sicxe_asm {

public:

private:

    string filename;
    
    struct listing_line{
        std::string address;
        std::unsigned int linenum;
        std::string label;
        std::string opcode;
        std::string operand;
        std::string machinecode;
        
        inline listing_line(){
        address="";
        linenum=0; 
        label="";
        opcode="";
        operand="";
        machinecode=""
        }
            
        std::string getaddress() const;
        std::unsigned int getlinenum() const;
        std::string getlabel() const;
        std::string getopcode() const;
        std::string getoperand() const;
        std::stirng getmachinecode() const;
        
    };

};



#endif //SICXE_ASM_H
