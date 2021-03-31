/*
 * File:	symbol.h
 */

# ifndef SYMBOL_H
# define SYMBOL_H
# include <string>
# include "type.h"

class Symbol{
    typedef std::string string;
    string name;
    Type type;
    
public:
    Symbol(const string &thisName, const Type &thisType);
    const string &_name() const{ return name; };
    const Type &_type() const{ return type; };
};
# endif /* Symbol_H */
