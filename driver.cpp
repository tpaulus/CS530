#include <iostream>
#include <stdlib.h>
#include "opcodetab.h"

using namespace std;

void attempt(opcodetab opcodetab, const string &s) {
    try {
        cout << "Machine Code of " << s << " is: " << opcodetab.get_machine_code(s) << endl;
        cout << "Size of " << s << " is: " << opcodetab.get_instruction_size(s) << endl;
    } catch (opcode_error_exception &exception) {
        cout << "ERROR - " << exception.getMessage() << endl;
    }
}

int main(int argc, char *argv[]) {
    opcodetab opcodetab;

    attempt(opcodetab, "ADD"); //case sensitivity
    attempt(opcodetab, "+aDd");

    cout << endl;

    attempt(opcodetab, "+WD"); //increment size
    attempt(opcodetab, "SSK");

    cout << endl;

    attempt(opcodetab, "+ADDR"); //type 2
    attempt(opcodetab, "+FLOAT"); //type 1

    cout << endl;

    attempt(opcodetab, "blarg"); //invalid
    attempt(opcodetab, "45");
    attempt(opcodetab, "+mulr+"); 
    attempt(opcodetab, "++ADD");

    cout << endl;

    attempt(opcodetab, ""); //empty

    cout << endl;

    attempt(opcodetab, "rsub"); //special
    attempt(opcodetab, "+rsub"); 
    attempt(opcodetab, "+RSUB");


}
