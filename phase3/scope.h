/*
 * File:	scope.h
 */

# ifndef SCOPE_H
# define SCOPE_H
# include <vector>
# include "symbol.h"

typedef std::vector<Symbol *> Symbols;

class Scope{
    typedef std::string string;
    
    Scope *enclosing;
    Symbols symbols;

public:
    Scope(Scope *_enclosing = nullptr): enclosing(_enclosing){};
    
    void insert(Symbol *thisSymbol);
    void remove(const string &name);
    Symbol *find(const string &name) const;
    Symbol *lookup(const string &name) const;
    
    Scope *_enclosing() const{ return enclosing; };
    const Symbols &_symbols() const{ return symbols; };
};
# endif /* SCOPE_H */
