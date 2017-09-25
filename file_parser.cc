#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <iomanip>

#include "file_parser.h"

using namespace std;

file_parser(string file_name) {

}

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

    string getLabel() const;

    string getOpcode() const;

    string getOperand() const;

    string getComment() const;
};

vector<line> victor; //add new elements with .push_back(<line>);
vector<string> contents;  // file contents in string form
string file_name; // Class variable for file_name

string line::getLabel() const {
    return label;
}

string line::getOpcode() const {
    return opcode;
}

string line::getOperand() const {
    return operand;
}

string line::getComment() const {
    return comment;
}

int size() {
    return static_cast<int>(victor.size());
}

// Prototypes
void print_error(const string &);

void read_file();

line line_parser(const string &raw_line);



/**
 * Reads the file from the command line and parses through the input.
 * @param file_name: assembly code source file.
 *
 */
void file_parser(string parse_name) {
    file_name = std::move(parse_name);
    read_file(); //loads contents with indexed lines.

    //loop to parse through contents line by line. Each line is passed through the line_parser.
    for (int i = 0; i < contents.size(); i++) {
        line_parser(contents[i]);
    }
}

/**
 * Parse through a raw line and assign the words to a line structure
 * the line structure will then be pushed onto victor.
 * @param raw_line: string containing the entire line to be parsed.
 */
line line_parser(const string &raw_line) {
    line tmp_line;    //temporary struct to be pushed onto victor.
    string *raw_index;  //pointer for the raw_line

    //Skips over spaces
    // while (!isblank(*raw_index)) {
    //     //there is probably a fancier c++ way to do this
    // }


    // TODO Implement conversion from string to line
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

    out << setw(label_col_width) << ios::left << setfill(' ') << label;
    out << setw(opcode_col_width) << ios::left << setfill(' ') << opcode;
    out << setw(operand_col_width) << ios::left << setfill(' ') << operand_col_width;
    out << comment << endl;

    return out;
}

/**
 * prints the indexes of vector victor
 * Note: May need to be fixed to iterate through the line struct at each index (works for strings atm)
 */
void print_file() {

    cout << "Now dumping what we read from file ..." << endl;
    for (int i = 0; i < victor.size(); i++)
        cout << victor[i] << endl;

    // outfile.open("output.txt", ios::out);
    // if (!outfile)
    //     print_error("Sorry, could not open the file for writing");

    // for (int i = 0; i < victor.size(); i++)
    //     outfile << victor[i] << endl;
    // outfile.close();


    for (const auto &i : victor) {
        cout << i << endl;
    }
}

void print_error(const string &s) {
    cout << s << endl;
    exit(1);
}

string get_token(unsigned int row, unsigned int column) {
    if (row < victor.size()) {
        //Is a valid row
        if (column == 0) {                //   0      1       2        3
            return victor[row].label;    //(label/opcode/operands/comments)
        } else if (column == 1) {
            return victor[row].opcode;
        } else if (column == 2) {
            return victor[row].operand;
        } else if (column == 3) {
            return victor[row].comment;
        }
    }
    //Not Valid row or column
    return "";
}
