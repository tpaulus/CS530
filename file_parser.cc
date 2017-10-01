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
    formatted_line tmp_line;    //temporary struct to be pushed onto victor.
    string token;
    string delimiters = " \t\n";

    if (!raw_line.empty()) {
        unsigned int column_start = 0;
        int col_space; // Distance to start of next column
        int tok_first;
        int tok_last;

        int column_num = 1; // Which column are you in

        bool isQuote = false;

        string column;

        while (column_num < 5) {
            if (column_start > raw_line.length()) {
                if (column_num == 4)
                    tmp_line.comment = "";
                break;
            }
            if (raw_line.find_first_of(" \t") > raw_line.length()) {
                tmp_line.label = raw_line;
                tmp_line.opcode = "";
                tmp_line.operand = "";
                tmp_line.comment = "";
                break;
            }

            column = raw_line.substr(column_start, 8);
            tok_last = column.find_first_not_of(delimiters, 0); // Start of token
            tok_first = column.find_first_of(delimiters, tok_last); // End of token

            if (column_num == 1 && (tok_last != -1)) {

                char first_letter = column[0];
                // Check if the column is a comment
                if (first_letter == '.') {
                    tmp_line.comment = raw_line.substr(column_start, raw_line.length() - column_start);
                    break;
                }

                tmp_line.label = column.substr(tok_last, tok_first - tok_last);
            } else if (column_num == 1 && tok_last == -1) {
                tmp_line.label = "";
            }

            if (column_num == 2 && (tok_last != -1)) {

                char first_letter = column[0];
                // Check if the column is a comment
                if (first_letter == '.') {
                    tmp_line.comment = raw_line.substr(column_start, raw_line.length() - column_start);
                    break;
                }
                tmp_line.opcode = column.substr(tok_last, tok_first - tok_last);
            } else if (column_num == 2 && tok_last == -1) {
                tmp_line.opcode = "";
            }

            if (column_num == 3 && (tok_last != -1)) {
                char first_letter = column[0];
                // Check if the column is a comment
                if (first_letter == '.') {
                    tmp_line.comment = raw_line.substr(column_start, raw_line.length() - column_start);
                    break;
                }

                if (column[1] == '\'') {
                    isQuote = true;
                }

                tmp_line.operand = column.substr(tok_last, tok_first - tok_last);
            } else if (column_num == 3 && tok_last == -1) {
                tmp_line.operand = "";
            }

            if (column_num == 4 && (tok_last != -1)) {

                char first_letter = column[0];

                // Check if the column is a comment, throw error if not
                if (first_letter == '.') {
                    tmp_line.comment = raw_line.substr(column_start, raw_line.length() - column_start);
                    break;
                } else {
                    // Throw comment error
                    file_parse_exception("Expected a comment.");
                }
            } else if (column_num == 4 && tok_last == -1) {
                tmp_line.comment = "";
            }

            // If the column is blank, move on to the next one.
            if (tok_last == -1) {
                column_start = column_start + 8;
                column_num = column_num + 1;
            } else {

                // If the column takes up all 8 characters, find the next delimiter/white space
                if (tok_first == -1) {
                    int column_end = raw_line.find_first_of(delimiters, (column_start + 8));
                    col_space = raw_line.find_first_not_of(delimiters, column_end);
                } else if (isQuote) {
                    // index of the last quote
                    int end_quote = raw_line.find_first_of('\'', (column_start + tok_first));

                    // index of where the next column begins after end of quote marks
                    int column_end = raw_line.find_first_of(delimiters, end_quote);
                    col_space = raw_line.find_first_not_of(delimiters, column_end);
                    isQuote = false;
                } else {
                    col_space = raw_line.find_first_not_of(delimiters, (column_start + tok_first));
                }

                column_start = col_space;
                column_num = column_num + 1;
            }
        }
    } else {
        tmp_line.label = "";
        tmp_line.comment = "";
        tmp_line.opcode = "";
        tmp_line.operand = "";
    }

    return tmp_line;
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








