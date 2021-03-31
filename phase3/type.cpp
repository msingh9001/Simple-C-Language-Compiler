/*
 * File:	type.cpp
 *
 */

# include <iostream>
# include "type.h"

using namespace std;

Type::Type(): _kind(ERROR){}

Type::Type(int thisSpecifier, unsigned thisIndirection): specifier(thisSpecifier), indirection(thisIndirection), _kind(SCALAR){}

Type::Type(int thisSpecifier, unsigned thisIndirection, unsigned thisLength): specifier(thisSpecifier), indirection(thisIndirection), length(thisLength), _kind(ARRAY){}

Type::Type(int thisSpecifier, unsigned thisIndirection, Parameters *theseParameters): specifier(thisSpecifier), indirection(thisIndirection), parameters(theseParameters), _kind(FUNCTION){}

bool Type::operator != (const Type &rhs) const{
   return !operator == (rhs);
}

bool Type::operator == (const Type &rhs) const
{
    if(_kind != rhs._kind)
        return false;
    
    if(_kind == ERROR)
        return true;
    
    if(specifier != rhs.specifier)
        return false;
    
    if(indirection != rhs.indirection)
        return false;
    
    if(_kind == SCALAR)
        return true;
    
    if(_kind == ARRAY)
        return length == rhs.length;
    
    if(!parameters || !rhs.parameters)
        return true;
    
    return *parameters == *rhs.parameters;
}
