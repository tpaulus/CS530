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

int main() {
    vector<line> victor; //add new elements with .push_back(<line>);


}
