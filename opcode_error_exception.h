/*  opcode_error_exception.h
    Exception class for opcodetab
*/    

#ifndef OPCODE_ERROR_EXCEPTION_H
#define OPCODE_ERROR_EXCEPTION_H
#include <string>

using namespace std;

class opcode_error_exception {

public:
    explicit opcode_error_exception(string s) {
        message = s;        
        }

    opcode_error_exception() {
        message = "An error has occurred";
        }
        
    string getMessage() {
        return message;
    }
    
private:
    string message;
};    
#endif
