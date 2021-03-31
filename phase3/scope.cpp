/*
 * File:	scope.cpp
 *
 */

# include <iostream>
# include "scope.h"

using namespace std;

void Scope::insert(Symbol *thisSymbol){
    symbols.push_back(thisSymbol);
}

void Scope::remove(const string &name){
    for(unsigned i = 0; i < symbols.size(); i++){
        if(name == symbols[i]->_name()){
            symbols.erase(symbols.begin()+i);
            break;
        }
    }
}

Symbol *Scope::find(const string &name) const{
    
    for(unsigned i = 0; i < symbols.size(); i++){
        if(symbols[i]->_name() == name)
            return symbols[i];
    }
    return nullptr;
}

Symbol *Scope::lookup(const string &name) const{
    Symbol *thisSymbol = find(name);
    
    if(thisSymbol != nullptr)
        return thisSymbol;
    return enclosing != nullptr ? enclosing->lookup(name) : nullptr;
}
