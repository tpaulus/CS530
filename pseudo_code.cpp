//
// Created by William Fox on 10/24/17.
//

//for each line in source;

line = nextline;
while(there are more lines && line.opperand != "START"){
    if(label || opcode || operand)
        throw exception
    line = nextline;
}

if(no more lines) throw exception; //No start

program name = line.label;
LOC_CTR counter = line.operand;

line = nextline;

while(line.opcode != "END"){
    write LOC_CTR;
    if(line.opcode is assembler directive){
        if(opcode == "EQU"){
            if(line.label == "") throw exception; //Nothing it put in symtab
            lookup line.label in symtab;
            if(found) throw exception; //Duplicate
            symtab.insert(label, line.operand, false);
//            else{
//                if(line.label != ""){
//                    lookup label in symtab
//                    if(found) throw exception; //Nothing to put in symtab
//                    symtab.insert(line.label, LOC_CTR, true);
//                }

            if(opcode == "BASE")
                base = line.operand; //String variable to symbol to lookup
            else if(opcode == "NOBASE")
                base = "";
            else if(opcode == "WORD")
                LOC_CTR += 3;
            else if(opcode == "BYTE"){
                toRun = substring between quotes;
                if(line.operand starts with 'C')
                    LOC_CTR += 1;
                else if(line.operand starts with X) {
                    if(token.length & 1 == 1) throw exception; //Odd number of characters
                    LOC_CTR += token.length >> 1; //One Byte is
                } //end ob BYTES
            } else if (opcode == "RESW")
                LOC_CTR += 3 * operand;
              else if( ocode == "RESB")
                LOC_CTR += operand;
        }     else{
                    if(line.label != ""){
                        toRun = symtab.search(label);
                        if(found) throw exception; //Already exists
                        symtab.insert(label, LOC_CTR);
                    }
                    size = lookup opcode;
                    if(!found) throw exception; //Invalid opcode
                    LOC_CTR += opcode.size;
              }
              write opcode & operand to line struct;
              line = nextline;
    }
}
