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
#include "symtab_exception.h"

using namespace std;

map<string, pair<int, bool> > symbol_table;

string sym_to_upper(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

symtab::symtab() {
    //TODO: Does anything belong in here?
}

void symtab::insert(pair<string, pair<int, bool> > obj) {

    obj.first = sym_to_upper(obj.first);
    if (contains(obj.first)) {
        throw symtab_exception(obj.first + ": Duplicate Label");

    }
    symbol_table.insert(obj);
}

void symtab::insert(string string1, int value, bool is_r) {
    symtab::insert(pair<string, pair<int, bool> >(string1, pair<int, bool>(value, is_r)));
}

void symtab::update(pair<string, pair<int, bool> > obj) {
    map<string, pair<int, bool> >::iterator m_iter = symbol_table.find(sym_to_upper(obj.first));
    //if key was found
    if (m_iter != symbol_table.end()) {
        m_iter->second = obj.second;
    }
    throw symtab_exception(obj.first + ": Not found");
}

void symtab::update(string string1, int value, bool is_r) {
    symtab::update(pair<string, pair<int, bool> >(string1, pair<int, bool>(value, is_r)));
}

bool symtab::contains(string key) {
    return symbol_table.find(sym_to_upper(key)) != symbol_table.end();
}

int symtab::get_value(string key) {
    key = sym_to_upper(key);
    if (symtab::contains(key)) {
        return symbol_table.at(key).first;
    }
    throw symtab_exception(key + ": Not found");
}

bool symtab::is_relative(string key) {
    key = sym_to_upper(key);
    if (symtab::contains(key)) {
        return symbol_table.at(key).second;
    }
    throw symtab_exception(key + ": Not found");
}
