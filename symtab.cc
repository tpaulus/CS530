/*
 * Alexander Pearson-Goulart, Athena Campbell, Jon Verne, Neha Nene, Tom Paulus, William Fox
 * cssc1015
 * Team Virginia
 * prog3
 * CS530, Fall 2017
 *
*/

#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include "symtab.h"

using namespace std;

map <string, pair<string, bool> > symbol_table;

string to_upper(string s) {
    transform(s.begin(), s.end(), s.begin(), ::to_upper);
    return s;
}

symtab::symtab() {
    //TODO: Does anything belong in here?
}

void symtab::insert(pair<string, pair<string, bool> > obj) {
    obj.first = to_upper(obj.first);
    symbol_table.insert(obj);
    //TODO: Should only insert if doesn't exist?
}

void symtab::insert(string string1, string string2, bool is_r) {
    symtab::insert(pair<string, pair<string, bool> > (string1, pair<string, bool>(string2, is_r)));
}

void symtab::update(pair<string, pair<string, bool> > obj) {
    map<string, pair<string, bool> >::iterator m_iter = symbol_table.find(to_upper(obj.first));
    //if key was found
    if (m_iter != symbol_table.end()){
        m_iter->second = obj.second;
    }
    //TODO: Else throw exception?
}

void symtab::update(string string1, string string2, bool is_r) {
    symtab::update(pair<string, pair <string, bool> > (string1, pair<string, bool>(string2, is_r)));
}

bool symtab::contains(string key) {
    return symbol_table.find(to_upper(key)) != symbol_table.end();
}

string symtab::get_value(string string1) {
    if(symtab::contains(string1)){
        return symbol_table.at(string1).first;
    }
    //TODO: Else throw exception?
}

bool symtab::is_relative(string string1) {
    if(symtab::contains(string1)){
        return symbol_table.at(string1).second;
    }
    //TODO: Else throw exception?
}