#include <iostream>
#include <fstream>
#include <vector>
#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Error, you must supply the name of the file " <<
        "to process at the command line." << endl;
        exit(1);
    }
    string filename = argv[1];
    try {
    file_parser parser(filename);
    parser.read_file();
    parser.print_file();
    cout << "Token at 2,0 is: " << parser.get_token(2,0) << endl;    
    cout << "Token at 2,1 is: " << parser.get_token(2,1) << endl;
    cout << "Token at 2,2 is: " << parser.get_token(2,2) << endl;
    cout << "Token at 2,3 is: " << parser.get_token(2,3) << endl;
    
    cout << "Token at 15,0 is: " << parser.get_token(15,0) << endl;    
    cout << "Token at 15,1 is: " << parser.get_token(15,1) << endl;
    cout << "Token at 15,2 is: " << parser.get_token(15,2) << endl;
    cout << "Token at 15,3 is: " << parser.get_token(15,3) << endl;    
            
    }
    catch(file_parse_exception excpt) {
        cout << "**Sorry, error " << excpt.getMessage() << endl;
    }
    
    
}
