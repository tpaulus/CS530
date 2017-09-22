#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cctype>

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
};

vector<line> victor; //add new elements with .push_back(<line>);

string line :: getLabel(string label){
	return label;
}
string line :: getOpcode(string opcode){
	return opcode;
}
string line :: getLabel(string operand){
	return operand;
}
string line :: getLabel(string comment){
	return comment;
}

int size(){
  return victor.size();
}

void print_error(string);

/*
 * Reads the file from the command line and parses through the input.
 * @param file_name: assembly code source file.
 * 
 */
void file_parser(file_name){
	
	read_file(); //loads contents with indexed lines.
	
	//loop to parse through contents line by line. Each line is passed through the line_parser.
	for(int i =0; i<contents.size;i++){
		line_parser(contents[i]);
	}
	return 0;
}

/*
 * Parse through a raw line and assign the words to a line structure
 * the line structure will then be pushed onto victor.
 * @param raw_line: string containing the entire line to be parsed.
 */
void line_parser(string raw_line){
	line tmp_line;	//temporary struct to be pushed onto victor.
	string* raw_index;  //pointer for the raw_line
	
	//Skips over spaces
	while(!isblank(*raw_index)){
		//there is probably a fancier c++ way to do this 
	}
	
	
}

/*
 * Takes the file assigned to file_name 
 * iterates line by line and assigns each to an index to vector contents
 */
void read_file() {
    ifstream infile; // input stream
    ofstream outfile; // output stream
    vector<string> contents;  // file contents
    int i=0; // vector index
    string line;

    if(argc != 2)
        print_error("You must specify a filename on the command line");

    infile.open(file_name,ios::in);
    if(!infile)
        print_error("Sorry, could not open the file for reading");

    while(!infile.eof()) {
        getline(infile,line);
        contents.push_back(line);
        }
    infile.close();

}
/**
 * prints the indexes of vector victor
 * Note: May need to be fixed to iterate through the line struct at each index (works for strings atm)
 */
void print_file(){ 

    cout << "Now dumping what we read from file ..." << endl;
    for(int i=0; i < victor.size(); i++)
        cout << victor[i] << endl;

    outfile.open("output.txt",ios::out);
    if(!outfile)
        print_error("Sorry, could not open the file for writing");

    for(int i=0; i < victor.size(); i++)
        outfile << victor[i] << endl;
    outfile.close();

}

void print_error(string s) {
    cout << s << endl;
    exit(1);
}


