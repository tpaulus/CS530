#include <iostream>
#include <map>
#include "opcodetab.h"

using namespace std;

map<string, pair<string, int> > marvin; // Don't make the space between > > go away - You will cry!

// ============== BEGIN Helper Functions ==============

bool isIncremented(const string &s) { return s.substr(0, 1) == "+"; }

string stripSpecial(string s) {
    if (isIncremented(s)) {
        return s.substr(1, s.size() - 1);  // TODO should this be 2?
    }

    return s;
}

string to_upper(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}


bool isSpecial(const string &s) { return to_upper(s) == "RSUB"; }

// ============== END Helper Functions ==============

opcodetab::opcodetab() {
    const int num_codes = 59;

    string opcode[num_codes] = {"ADD", "ADDF", "ADDR", "AND", "CLEAR", "COMP", "COMPF",
                                "COMPR", "DIV", "DIVF", "DIVR", "FIX", "FLOAT", "HIO", "J", "JEQ", "JGT",
                                "JLT", "JSUB", "LDA", "LDB", "LDCH", "LDF", "LDL", "LDS", "LDT", "LDX",
                                "LPS", "MUL", "MULF", "MULR", "NORM", "OR", "RD", "RMO", "RSUB", "SHIFTL",
                                "SHIFTR", "SIO", "SSK", "STA", "STB", "STCH", "STF", "STI", "STL", "STS",
                                "STSW", "STT", "STX", "SUB", "SUBF", "SUBR", "SVC", "TD", "TIO", "TIX",
                                "TIXR", "WD"};

    string mcode[num_codes] = {"18", "58", "90", "40", "B4", "28", "88", "A0", "24",
                               "64", "9C", "C4", "C0", "F4", "3C", "30", "34", "38", "48", "00", "68",
                               "50", "70", "08", "6C", "74", "04", "D0", "20", "60", "98", "C8", "44",
                               "D8", "AC", "4C", "A4", "A8", "F0", "EC", "0C", "78", "54", "80", "D4",
                               "14", "7C", "E8", "84", "10", "1C", "5C", "94", "B0", "E0", "F8", "2C",
                               "B8", "DC"};

    int opsize[num_codes] = {3, 3, 2, 3, 2, 3, 3, 2, 3, 3, 2, 1, 1, 1, 3, 3, 3, 3,
                             3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 3, 3, 2, 3, 2, 2, 1, 3, 3, 3, 3,
                             3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 3, 1, 3, 2, 3};


    for (int i = 0; i < num_codes; i++) {
        marvin.insert(pair<string, pair<string, int> >(opcode[i], pair<string, int>(mcode[i], opsize[i])));
    }

} //opcodetab()

/**
 * Get the Size of a Given Instruction based off of its opcode
 *
 * @param s Opcode String
 * @return Instruction Size, between 1 and 4
 */
int opcodetab::get_instruction_size(string s) {
    if (isValid(s)) {
        int instruction_size = marvin.at(s).second;

        if (isIncremented(s) && instruction_size == 3 && !isSpecial(s)) {
            return instruction_size + 1;
        }
        return instruction_size;
    }

    throw opcode_error_exception("You done fudged!");
    // TODO Throw some crap!
}

/**
 * Get HEX Machine code for a given opcode
 *
 * @param s Opcode String
 * @return HEX Machine Code
 */
string opcodetab::get_machine_code(string s) {
    if (isValid(s)) {
        return marvin.at(s).first;
    }

    throw opcode_error_exception("You done fudged!");
    // TODO Throw some crap!
}

/**
 * Checks if the supplied opcode is valid
 *
 * @param opcode Opcode String Ex: "ADD"
 * @return is valid opcode
 */
bool opcodetab::isValid(string opcode) {
    return marvin.find(stripSpecial(to_upper(opcode))) != marvin.end();
}
