/*
 * Alexander Pearson-Goulart, Athena Campbell, Jon Verne, Neha Nene, Tom Paulus, William Fox
 * cssc1015
 * Team Virginia
 * prog3
 * CS530, Fall 2017
 *
*/


#ifndef SYMTAB_H
#define SYMTAB_H


#include<string>
#include<map>
//#include<symtab_exception.h>

using namespace std;

class symtab {
public:
    //ctor
    //Creates new dictionary structure using STL map
    symtab();

    //Obj insert
    void insert(pair<string, pair<int, bool> >);

    //Primative Insert
    void insert(string, int, bool);

    //Updates the entry using an object
    void update(pair<string, pair<int, bool> >);

    //Updates the entry using Primitives
    void update(string, int, bool);

    //Returns true if key exists, false if not
    bool contains(string);

    //Returns the value (Adress/Value) of the key
    int get_value(string);

    //Returns true if the key is relative, false if not
    bool is_relative(string);

private:

    //Key <Label> Value<Address/Value, is_relative>
    map<string, pair<int, bool> > symbol_table;

};

#endif //SYMTAB_H
