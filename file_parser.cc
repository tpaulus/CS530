#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

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

/*  CS530 Fall 2017
    How to read and write text files
    Alan Riggins
*/


void print_error(string);

int read_file() {
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

        //start parser here
    while(!infile.eof()) {
        getline(infile,line);
        contents.push_back(line);
        }
    infile.close();

}

void print_file(){  //in progress

    cout << "Now dumping what we read from file ..." << endl;
    for(int i=0; i < contents.size(); i++)
        cout << contents[i] << endl;

    outfile.open("output.txt",ios::out);
    if(!outfile)
        print_error("Sorry, could not open the file for writing");

    for(int i=0; i < contents.size(); i++)
        outfile << contents[i] << endl;
    outfile.close();

}

void print_error(string s) {
    cout << s << endl;
    exit(1);
}


