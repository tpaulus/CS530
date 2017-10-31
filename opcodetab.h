/*
 * Alexander Pearson-Goulart, Athena Campbell, Jon Verne, Neha Nene, Tom Paulus, William Fox
 * cssc1015
 * Team Virginia
 * prog2
 * CS530, Fall 2017
 *
*/

#ifndef OPCODETAB_H
#define OPCODETAB_H

#include<string>
#include<map>
#include "opcode_error_exception.h"

using namespace std;

class opcodetab {
public:
    // ctor
    // creates a new dictionary structure and loads all of the opcodes for
    // the SIC/XE architecture into the table.  Use the STL
    // map for this.
    opcodetab();

    // takes a SIC/XE opcode and returns the machine code
    // equivalent as a two byte string in hexadecimal.
    // Example:  get_machine_code("ADD") returns the value 18
    // Note that opcodes may be prepended with a '+'.
    // throws an opcode_error_exception if the opcode is not
    // found in the table.
    string get_machine_code(string);

    // takes a SIC/XE opcode and returns the number of bytes
    // needed to encode the instruction, which is an int in
    // the range 1..4.
    // NOTE: the opcode must be prepended with a '+' for format 4.
    // throws an opcode_error_exception if the opcode is not
    // found in the table.
    int get_instruction_size(string);

    bool is_valid(string);

private:
    map<string, pair<string, int> > marvin;

    bool is_incremented(const string &);
    string strip_incremented(const string &);
    string opcode_to_upper(string);
    bool is_special(const string &);

    };



#endif
