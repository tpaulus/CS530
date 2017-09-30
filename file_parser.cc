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

struct formatted_line {
    //Fields
    string label;
    string opcode;
    string operand;
    string comment;

    string getlabel() const;
    string getopcode() const;
    string getoperand() const;
    string getcomment() const;

    //Constructor
    formatted_line(){
        label = "";
        opcode = "";
        operand = "";
        comment = "";
    }
};

string formatted_line::getlabel() const {
    return label;
}

string formatted_line::getopcode() const {
    return opcode;
}

string formatted_line::getoperand() const {
    return operand;
}

string formatted_line::getcomment() const {
    return comment;
}

//Class Level Variables

vector <formatted_line> victor(100); //add new elements with .push_back(<line>);
vector <string> file_contents(100);  // file contents in string form
string file_name;

//Constructor
file_parser::file_parser(const string f_n) {
    file_name = f_n;
}
file_parser::~file_parser();

string file_parser::get_token(unsigned int, unsigned int) {

}

void file_parser::read_file() {

}

void file_parser::print_file() {

}

formatted_line file_parser::line_parser(std::string) {

}


int file_parser::size() {
    return static_cast<int>(victor.size());
}



