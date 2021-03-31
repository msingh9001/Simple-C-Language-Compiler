/*
 * File:	symbol.cpp
 *
 */

# include <iostream>
# include "symbol.h"

using namespace std;

Symbol::Symbol(const string &thisName, const Type &thisType){
    name = thisName;
    type = thisType;
}
