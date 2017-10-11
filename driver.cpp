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

    attempt(opcodetab, "ADD");
    attempt(opcodetab, "Add");

    cout << endl;

    attempt(opcodetab, "LDA");
    attempt(opcodetab, "+LDA");

    cout << endl;

    attempt(opcodetab, "blarg");
    attempt(opcodetab, "blarg");

    cout << endl;

    attempt(opcodetab, "+rsub");
    attempt(opcodetab, "+RSUB");
    attempt(opcodetab, "+ADDR");
    attempt(opcodetab, "+FIX");
}
