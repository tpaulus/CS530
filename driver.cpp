#include <iostream>
#include <stdlib.h>
#include "opcodetab.h.h"
using namespace std;

int main(int argc, char *argv[]) {
    try {
    opcodetab marvin()
    cout << "Machine Code of Add is: " << marvin.get_machine_code("Add") << endl;    
    cout << "Machine Code of ADD is: " << marvin.get_machine_code("ADD") << endl;    
    cout << "Machine Code of LDA is: " << marvin.get_machine_code("LDA") << endl; 
    cout << "Machine Code of +LDA is: " << marvin.get_machine_code("+LDA") << endl;    

    cout << "Size of +LDA is: " << marvin.get_instruction_size("+LDA") << endl;
    cout << "Size of LDA is: " << marvin.get_instruction_size("LDA") << endl;    

    cout << "Machine Code of blarg is: " << marvin.get_machine_code("blarg") << endl;    
    cout << "Size of blarg is: " << marvin.get_instruction_size("blarg") << endl;  
    cout << "Size of +rsub is: " << marvin.get_instruction_size("+rsub") << endl;  

    }
    catch(file_parse_exception excpt) {
        cout << "**Sorry, error " << excpt.getMessage() << endl;
    }
    
    
}
