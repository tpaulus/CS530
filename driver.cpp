#include <iostream>
#include <stdlib.h>
#include "opcodetab.h"

using namespace std;

void attempt(opcodetab marvin, string s) {
    try {
        cout << "Machine Code of " << s << " is: " << marvin.get_machine_code(s) << endl;
        cout << "Size of " << s << " is: " << marvin.get_instruction_size(s) << endl;
    } catch (opcode_error_exception exception) {
        cout << "**Sorry, error " << exception.getMessage() << endl;
    }
}

int main(int argc, char *argv[]) {
    opcodetab marvin;

    attempt(marvin, "ADD");
    attempt(marvin, "Add");

    attempt(marvin, "LDA");
    attempt(marvin, "+LDA");

    attempt(marvin, "blarg");
    attempt(marvin, "+rsub");
}
