/*
 * Alexander Pearson-Goulart, Athena Campbell, Jon Verne, Neha Nene, Tom Paulas, William Fox
 * csscxxxx
 * prog1
 * CS530, Fall 2017
 *
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <iomanip>
#include <string>

#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;


//Struct Implementations

struct formated_line {

};

formated_line::formatted_line(){
    label = "";
    opcode = "";
    operand = "";
    comment = "";
}

string formated_line::getlabel() const {
    return label;
}

string formated_line::getopcode() const {
    return opcode;
}

string formated_line::getoperand() const {
    return operand;
}

string formated_line::getcomment() const {
    return comment;
}

//Class Level Variables

vector <formated_line> victor(100); //add new elements with .push_back(<line>);
vector <string> contents(100);  // file contents in string form
string file_name;

//Constructor
file_parser::file_parser(const string f_n) {
    file_name = f_n;
}


int file_parser::size() {
    return static_cast<int>(victor.size());
}



