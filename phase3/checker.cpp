/*
 * File:	checker.cpp
 *
 */

# include <iostream>
# include "checker.h"
# include "scope.h"
# include "tokens.h"
# include "lexer.h"

using namespace std;

static string redefined = "redefinition of '%s'";
static string conflicting = "conflicting types for '%s'";
static string redeclaration = "redeclaration of '%s'";
static string undeclared = "'%s' undeclared";
static string type_void = "'%s' has type void";
Scope* _global = nullptr;
Scope* _current = nullptr;

void openScope()
{
    _current = new Scope(_current);
    if(_global == nullptr){
        _global = _current;
        
        cout << "open file scope" << endl;
    }else{
        
        cout << "open scope" << endl;
    }
}

void closeScope()
{
    _current = _current->_enclosing();
    cout << "close scope" << endl;
}

void declareVariable(const string &name, const Type &_type){
    
    Symbol *temp = _current->find(name);
    
    //array of void is illegal i.e. void arr[5];
    if(_type._indirection() == 0 && _type._specifier() == VOID){
        report(type_void, name);
        cout << "void error" << endl;
    }else if(temp == nullptr){
        Symbol* thisSymbolPtr = new Symbol(name, _type);
        _current->insert(thisSymbolPtr);
        cout << "declare " << name << " as (" << _type._specifier() << "," << _type._indirection() << ", SCALAR)" << endl;
    }else if(_current->_enclosing() != nullptr){
        cout << "redeclaration for " << name << endl;
        report(redeclaration, name);
    }else if(temp->_type() != _type){
        cout << "conflicting types for " << name << endl;
        report(conflicting, name);
    }
}
    
    
    
 /*
    if(_global->find(name) == nullptr && _current->find(name) == nullptr){
        //array of void is illegal i.e. void arr[5];
        if(_type->isArray() && _type->_indirection() == 0 && _type->_specifier() == VOID){
            report(type_void, name);
            break;
        }
        Symbol thisSymbol = Symbol(name, _type);
        Symbol thisSymbolPtr = &thisSymbol;
        _current->insert(thisSymbolPtr);
        cout << "declare" << name << "as (" << printTypespec(typespec) << "," << indirection << ", SCALAR)" << endl;
    }else if(_global == _current)
    
  
  
  
  
  Each function is declared in the global scope. The type of the function is “function returningT,” whereThas aspecifier ofspecifieralong with any pointer declarators specified as part ofpointers. Any previous declaration mustbe identical [E2], ignoring any parameters specified as part of a previous function definition.
*/

void declareFunction(const string &name, const Type &_type){
    Symbol* temp = _global->find(name);
    if(temp == nullptr){
        Symbol* thisSymbolPtr = new Symbol(name, _type);
        _global->insert(thisSymbolPtr);
        cout << "declare " << name << " as (" << _type._specifier() << "," << _type._indirection() << ", FUNCTION)" << endl;
        
    }else if(temp->_type()._specifier() != _type._specifier() || temp->_type()._indirection() != _type._indirection() || !temp->_type().isFunction()){
        cout << "conflicting types for " << name << endl;
        report(conflicting, name);
    }else if(_current != nullptr)
        report(redeclaration, name);
//        if(temp->_type()._specifier() != _type._specifier() || temp->_type()._indirection() != _type._indirection() || !temp->_type().isFunction()){
//            cout << "conflicting types for " << name << endl;
//            report(conflicting, name);
//        }
//    }
    
}

void defineFunction(const string &name, const Type &_type){
    Symbol* temp = _global->find(name);
    if(temp == nullptr){
        Symbol* thisSymbolPtr = new Symbol(name, _type);
        _global->insert(thisSymbolPtr);
        cout << "define " << name << " as (" << _type._specifier() << "," << _type._indirection() << ", FUNCTION)" << endl;
        
    }else if(temp->_type()._parameters() != nullptr){
        cout << "redefined " << name << endl;
        report(redefined, name);
    }else{
        if(temp->_type()._specifier() != _type._specifier() || temp->_type()._indirection() != _type._indirection() || !temp->_type().isFunction()){
            cout << "conflicting types for " << name << endl;
            report(conflicting, name);
        }
            _current->remove(name);
            cout << "removing old declaration for: " << name << endl;
            Symbol* thisSymbolPtr = new Symbol(name, _type);
            _global->insert(thisSymbolPtr);
            cout << "inserting new declaration for: " << name << endl;
        }
        cout << "define " << name << " as (" << _type._specifier() << "," << _type._indirection() << ", FUNCTION)" << endl;
}

void checkID(const string &name){
    cout << "check" << name << endl;
    Symbol* temp = _current->lookup(name);
    if(temp == nullptr)
        report(undeclared, name);
}
