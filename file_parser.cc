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
    formatted_line() {
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

formatted_line line_parser(string raw_line) {
    //Change to real value
    return formatted_line();
}
void file_parser::read_file() {
    ifstream infile; // input stream
    string raw_line;
    vector<string>::iterator v_iter;

    if (file_name.empty())
        file_parse_exception("You must specify a filename on the command line");

    infile.open(file_name.c_str(), ios::in);

    if (!infile) //Unreachable code?
        file_parse_exception("Sorry, could not open the file for reading");

    while (!infile.eof()) {
        getline(infile, raw_line);
        file_contents.push_back(raw_line);
    }
    
    infile.close();

    //Each line is passed through the line_parser then pushed into victor
    for (v_iter = file_contents.begin(); v_iter != file_contents.end(); v_iter++) {
        victor.push_back(file_parser::line_parser(*v_iter));
    }
}

void file_parser::print_file() {

}

string file_parser::get_token(unsigned int row, unsigned int column) {
    if (column == 0) {                  //   0      1       2        3
        return victor.at(row).label;    //(label/opcode/operands/comments)
    } else if (column == 1) {
        return victor.at(row).opcode;
    } else if (column == 2) {
        return victor.at(row).operand;
    } else if (column == 3) {
        return victor.at(row).comment;
    }
    //No matching column
    return "";
}

int file_parser::size() {
    return static_cast<int>(victor.size());
}








