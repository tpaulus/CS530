#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cctype>

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

    string getLabel();

    string getOpcode();

    string getOperand();

    string getComment();
};

vector<line> victor; //add new elements with .push_back(<line>);
string file_name;

string line::getLabel() {
    return label;
}

string line::getOpcode() {
    return opcode;
}

string line::getOperand() {
    return operand;
}

string line::getComment() {
    return comment;
}

int size() {
    return static_cast<int>(victor.size());
}

// Prototypes
void print_error(const string &);

vector<string> read_file();

line line_parser(const string &raw_line);



/**
 * Reads the file from the command line and parses through the input.
 * @param file_name: assembly code source file.
 * 
 */
void file_parser(string parse_name) {
    file_name = std::move(parse_name);
    vector<string> contents = read_file(); //loads contents with indexed lines.

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
    while (!isblank(*raw_index)) {
        //there is probably a fancier c++ way to do this
    }


    // TODO Implement conversion from string to line
    return nullptr;
}

/**
 * Takes the file assigned to file_name 
 * iterates line by line and assigns each to an index to vector contents
 */
vector<string> read_file() {
    ifstream infile; // input stream
    ofstream outfile; // output stream
    vector<string> contents;  // file contents
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

    return contents;
}

/**
 * prints the indexes of vector victor
 * Note: May need to be fixed to iterate through the line struct at each index (works for strings atm)
 */
void print_file() {

    cout << "Now dumping what we read from file ..." << endl;
    for (int i = 0; i < victor.size(); i++)
        cout << victor[i] << endl;

    outfile.open("output.txt", ios::out);
    if (!outfile)
        print_error("Sorry, could not open the file for writing");

    for (int i = 0; i < victor.size(); i++)
        outfile << victor[i] << endl;
    outfile.close();

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
