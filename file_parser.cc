#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <iomanip>
#include <string>

#include "file_parser.h"

using namespace std;



struct line {
    string label;
    string opcode;
    string operand;
    string comment;

    line() {
        label = "";
        opcode = "";
        operand = "";
        comment = "";
    }

    string getlabel() const;

    string getopcode() const;

    string getoperand() const;

    string getcomment() const;
};

vector<line> victor (100); //add new elements with .push_back(<line>);
vector<string> contents (100);  // file contents in string form
string file_name; // Class variable for file_name

string line::getlabel() const {
    return label;
}

string line::getopcode() const {
    return opcode;
}

string line::getoperand() const {
    return operand;
}

string line::getcomment() const {
    return comment;
}

int size() {
    return static_cast<int>(victor.size());
}

// Prototypes
void print_error(const string &);

void read_file();

line line_parser(string);

/**
 * Constructor
 * Reads the file from the command line and saves it locally
 * @param file_name: assembly code source file.
 *
 */

file_parser::file_parser(const string file_name) {
    file_name = std::move(file_name);
}


// void file_parser(string parse_name) {
//     file_name = std::move(parse_name);
//     read_file(); //loads contents with indexed lines.

//     //loop to parse through contents line by line. Each line is passed through the line_parser.
//     for (int i = 0; i < contents.size(); i++) {
//         line_parser(contents.at(i));
//     }
// }

/**
 * Parse through a raw line and assign the words to a line structure
 * the line structure will then be pushed onto victor.
 * @param raw_line: string containing the entire line to be parsed.
 */
line line_parser(string raw_line) {
    line tmp_line;    //temporary struct to be pushed onto victor.

    string token;

    string delimiters = " \t\n";

    if(!raw_line.empty()) {
        int column_start = 0;
        int col_space; // Distance to start of next column
        int tok_first;
        int tok_last;

        int column_num = 1; // Which column are you in

        bool isQuote = false;

        string column;     

        while(column_num < 5) {

            if(column_start > raw_line.length()) {
                if(column_num == 4)
                    tmp_line.comment = "";
                break;
            }

            if(raw_line.find_first_of(" \t") > raw_line.length()) {
                tmp_line.label = raw_line;
                tmp_line.opcode = "";
                tmp_line.operand = "";
                tmp_line.comment = "";
                break;
            }

            column = raw_line.substr(column_start, 8);

            tok_last = column.find_first_not_of(delimiters, 0); // Start of token
            tok_first = column.find_first_of(delimiters, tok_last); // End of token

            if(column_num == 1 && (tok_last != -1)) {

                char first_letter = column[0];
        
                // Check if the column is a comment
                if(first_letter == '.') {
                    tmp_line.comment = raw_line.substr(column_start, raw_line.length() - column_start);
                    break;
                }

                tmp_line.label = column.substr(tok_last, tok_first-tok_last);
            }
            else if(column_num == 1 && tok_last == -1) {
                tmp_line.label = "";
            }
            
            if(column_num == 2 && (tok_last != -1)) {

                char first_letter = column[0];
                
                // Check if the column is a comment
                if(first_letter == '.') {
                    tmp_line.comment = raw_line.substr(column_start, raw_line.length() - column_start);
                    break;
                }

                tmp_line.opcode = column.substr(tok_last, tok_first-tok_last);
            }
            else if(column_num == 2 && tok_last == -1) {
                tmp_line.opcode = "";
            }
            
            if(column_num == 3 && (tok_last != -1)) {

                char first_letter = column[0];
                
                // Check if the column is a comment
                if(first_letter == '.') {
                    tmp_line.comment = raw_line.substr(column_start, raw_line.length() - column_start);
                    break;
                }

                if(column[1] == '\'') {
                    isQuote = true;
                }

                tmp_line.operand = column.substr(tok_last, tok_first-tok_last);
            }
            else if(column_num == 3 && tok_last == -1) {
                tmp_line.operand = "";  
            }
            
            if(column_num == 4 && (tok_last != -1)) {

                char first_letter = column[0];
                
                // Check if the column is a comment, throw error if not
                if(first_letter == '.') {
                    tmp_line.comment = raw_line.substr(column_start, raw_line.length() - column_start);
                    break;
                }
                else {
                    cout << "ERROR: Expected a comment." << endl;
                }
            }
            else if(column_num == 4 && tok_last == -1) {
                tmp_line.comment = "";  
            }

            // If the column is blank, move on to the next one.
            if(tok_last == -1) {
                column_start = column_start + 8;
                column_num = column_num + 1;
            }
            else {

                // If the column takes up all 8 characters, find the next delimiter/white space
                if(tok_first == -1) {
                    int column_end = raw_line.find_first_of(delimiters, (column_start + 8));
                    col_space = raw_line.find_first_not_of(delimiters, column_end);
                }
                else if(isQuote) {
                    // index of the last quote
                    int end_quote = raw_line.find_first_of('\'', (column_start + tok_first));

                    // index of where the next column begins after end of quote marks
                    int column_end = raw_line.find_first_of(delimiters, end_quote);
                    col_space = raw_line.find_first_not_of(delimiters, column_end);
                    isQuote = false;
                }
                else {
                    col_space = raw_line.find_first_not_of(delimiters, (column_start + tok_first));
                }
                
                column_start = col_space;
                column_num = column_num + 1;
            }
        }
    }
    else {
        tmp_line.label = "";
        tmp_line.comment = "";
        tmp_line.opcode = "";
        tmp_line.operand = "";
    }

    return tmp_line;
}

/**
 * Takes the file assigned to file_name
 * iterates line by line and assigns each to an index to vector contents
 */
void read_file() {
    ifstream infile; // input stream
    int i = 0; // vector index
    string line;

    if (file_name.empty())
        print_error("You must specify a filename on the command line");

    infile.open(file_name, ios::in);
    if (!infile)
        print_error("Sorry, could not open the file for reading");

    while (!infile.eof()) {
        getline(infile, line);
        contents.push_back(line);
    }
    infile.close();

    //loop to parse through contents line by line. Each line is passed through the line_parser.
    for (int i = 0; i < contents.size(); i++) {
        victor.push_back(line_parser(contents.at(i)));
    }
}

/**
 * Stream out a Line Struct
 *
 * @param out Output Stream
 * @param value Line to Print
 * @return Output Stream
 */
ostream &operator<<(ostream &out, const line &value) {
    const int label_col_width = 8;
    const int opcode_col_width = 8;
    const int operand_col_width = 8;

    out << setw(label_col_width) << ios::left << setfill(' ') << value.getlabel();
    out << setw(opcode_col_width) << ios::left << setfill(' ') << value.getopcode();
    out << setw(operand_col_width) << ios::left << setfill(' ') << value.getoperand();
    out << value.getcomment() << endl;

    return out;
}

/**
 * prints the indexes of vector victor
 * Note: May need to be fixed to iterate through the line struct at each index (works for strings atm)
 */
void print_file() {
    vector<int>::iterator v_iter;
    
    for (v_iter = victor.begin(); v_iter != victor.end(); v_iter++) {
        cout << *v_iter << endl;
    }
}

void print_error(const string &s) {
    cout << s << endl;
    exit(1);
}

string get_token(unsigned int row, unsigned int column) {
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
