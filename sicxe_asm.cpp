/*
 * Alexander Pearson-Goulart, Athena Campbell, Jon Verne, Neha Nene, Tom Paulus, William Fox
 * cssc1015
 * Team Virginia
 * prog3
 * CS530, Fall 2017
 *
*/
#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include "sicxe_asm.h"
using namespace std;

bool is_comment_or_empty(file_parser::formatted_line line);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "ERROR - You must supply the name of the file to assemble." << endl;
        exit(1);
    }
    string filename = argv[1];

    file_parser parser(filename);
    try{
        parser.read_file();
    }catch (file_parse_exception fileParseException){
        cout << "ERROR - " << fileParseException.getMessage() << endl; //This should have a line number already
        exit(1);
    }
    vector <file_parser::formatted_line> listing_vector(0);
    vector<file_parser::formatted_line>::iterator line_iter;
    //Loads new Vector of Structs
    for(int i = 0; i < parser.size(); i++) {
        listing_vector.push_back(parser.get_struct((unsigned int)i));
    }

    line_iter = listing_vector.begin(); //Grabs first line
    //While more lines and operand != start
    while(line_iter != listing_vector.end() && sicxe_asm::to_uppercase(line_iter->opcode) != "START"){
        if(!is_comment_or_empty(*line_iter)){
            cout << "ERROR - No executable code before START Directive: Line " << line_iter->linenum << endl;
            cout << *line_iter << endl;
            exit(2);
        }
        line_iter++; //Grab next line
    }
    if(line_iter == listing_vector.end()){
        cout << "ERROR - No START Directive" << endl; //We can't know the line number, following the iterator is nullptr
        exit(3);
    }
    //Get Program name and starting location counter
    string program_name = line_iter->label;
    int location_counter = sicxe_asm::hex_to_int(line_iter->operand);
    //TODO: This is now where start is in the flowchart
    string BASE = "";
    
    
   //starts part D
    else{
	if ((line_iter->label) != ''){
		if(symtab.contains(line_iter->label))
			cout << "ERROR - Duplicate label on line " << line_iter->line_num << endl;
			exit(4);
		symtab.insert((line_iter->label), location_counter, true);
	    }
	 string comp = sicxe_asm::to_uppercase(line_iter->opcode);
	 if (comp == "BASE")
		BASE = (line_iter->operand);
	 else if (comp == "NOBASE")
		BASE = "";
	 else if (comp == "WORD")
		location_counter += 3;
	 else if (comp == "BYTE"){
		size_t pos_left = (line_iter->operand).find_first_of("'");      
          size_t pos_right = (line_iter->operand).find_last_of("'");  
         if (pos_left != "npos" && pos_right != "npos") //if there are two quotes
                string token = (line_iter->operand.substr(pos_left + 1, pos_right - pos_left - 1)
         else{
                cout << "ERROR - Mismatched quotes in BYTE operand on line " << line_iter->line_num << endl;
		exit(5);
	  }
          if ((line_iter->operand).find("C") == 0) //starts with C		
		location_counter++; //TODO: Check to see if will always be just +1 
	  else if((line_iter->operand).find("X") == 0){  //starts with X
		if((token.length &1) == 1){
			cout << "ERROR - Invalid operand for BYTE on line " << line_iter->line_num << endl;
			exit(6);
		}
		location_counter += (token.length > > 1)			
		}
		else {
			cout << "ERROR - Invalid operand for BYTE on line " << line_iter->line_num << endl;
			exit(7);
		}
          }
	    else if (comp == "RESW")	
			location_counter += 3*(line_iter->operand); 
	    else if (comp == "RESB")
			location_counter += (line_iter->operand); 
	   
   }

}

bool is_comment_or_empty(file_parser::formatted_line line) {
    return line.label.empty() && line.opcode.empty() && line.operand.empty();
}

