/*
 * Alexander Pearson-Goulart, Athena Campbell, Jon Verne, Neha Nene, Tom Paulas, William Fox
 * cssc1015
 * Team Virginia
 * prog1
 * CS530, Fall 2017
 *
*/

#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

class file_parser {
public:
    struct formatted_line {
        //Fields
        std::string label;
        std::string opcode;
        std::string operand;
        std::string comment;
        std::string address;
        std::string formatted_machinecode;
        unsigned int machinecode;
        unsigned int linenum;
        //Methods
        inline formatted_line() {
            label = "";
            opcode = "";
            operand = "";
            comment = "";
            address = "";
            machinecode = 0;
            linenum = 0;
        }
        std::string getlabel() const;
        std::string getopcode() const;
        std::string getoperand() const;
        std::string getcomment() const;
        std::string getaddress() const;
        std::string get_formatted_machinecode() const;
        unsigned int getmachinecode();
        unsigned int getlinenum();
    };
    // ctor, filename is the parameter.  A driver program will read
    // the filename from the command line, and pass the filename to
    // the file_parser constructor.  Filenames must not be hard-coded.
    file_parser(std::string);

    // dtor
    ~file_parser();

    // reads the source file, storing the information is some
    // auxiliary data structure you define in the private section.
    // Throws a file_parse_exception if an error occurs.
    // if the source code file fails to conform to the above
    // specification, this is an error condition.
    void read_file();

    // returns the token found at (row, column).  Rows and columns
    // are zero based.  Returns the empty string "" if there is no
    // token at that location. column refers to the four fields
    // identified above.
    std::string get_token(unsigned int, unsigned int);

    // prints the source code file to stdout.  Should not repeat
    // the exact formatting of the original, but uses tabs to align
    // similar tokens in a column. The fields should match the
    // order of token fields given above (label/opcode/operands/comments)
    void print_file();

    // returns the number of lines in the source code file
    int size();

    struct formatted_line get_struct(unsigned int);

    // your variables and private methods go here



private:
    //Class Level Variables
    std::vector<formatted_line> victor;
    std::vector<std::string> file_contents;
    std::string file_name;
    //Methods
    formatted_line line_parser(std::string, unsigned int);
    //Always good to make friends, especially if it makes your compiler happy
    friend std::ostream &operator<<(std::ostream &out, const file_parser::formatted_line &f_l);
};

inline std::ostream &operator<<(std::ostream &out, const file_parser::formatted_line &f_l) {
    const int label_col_width = 8;
    const int opcode_col_width = 8;
    const int operand_col_width = 8;

    out << std::setw(label_col_width) << std::left << std::setfill(' ') <<f_l.label;
    out << std::setw(opcode_col_width) << std::left << std::setfill(' ') << f_l.opcode;
    out << std::setw(operand_col_width) << std::left << std::setfill(' ') << f_l.operand;
    out << f_l.comment << std::endl;

    return out;
    }


#endif
