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

string get_token(unsigned int row, unsigned int column){
  if(row < victor.size()){
    //Is a valid row
    if(column == 1){                //   0      1       2        3
      return victor[row].label;    //(label/opcode/operands/comments)
    } else if (column == 2) {
      return victor[row].opcode;
    } else if (column == 3) {
      return victor[row].operand;
    } else if (column == 4) {
      return victor[row].comment;
    }
  }
  //Not Valid row or column
  return "";
}
