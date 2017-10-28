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
#include "file_parser.cc"
#include "opcodetab.cc"

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

bool skip_check(file_parser,int);

int main(int argc, char *argv[]) {

    string filename = argv[1];
    file_parser parser(filename);
    parser.read_file();

    vector <listing_line> list_vec(100);

    listing_line tmp_line;


    for(int i = 0; i < parser.size(); i++)
    {
        if(skip_check(parser,i))
            continue;
        tmp_line.linenum = i;
        tmp_line.label = parser.get_token(i,0);
        tmp_line.opcode = parser.get_token(i,1);
        tmp_line.operand = parser.get_token(i,2);
        list_vec.push_back(tmp_line);
    }

}

bool skip_check(file_parser parser, int row_num)
{
    string comment = parser.get_token(row_num,3);
    string label = parser.get_token(row_num,0);
    string opcode = parser.get_token(row_num,1);

    if(label.empty() && opcode.empty()&& comment[0] == '.')
        return true;
    if(label.empty() && opcode.empty() && comment.empty())
        return true;
    return false;
}
                                                                                       
