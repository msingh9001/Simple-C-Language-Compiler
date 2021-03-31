# include "Generator.h"
# include "Tree.h"
# include <iostream>
# include "tokens.h"

int callerSize = 0;

using namespace std;


static ostream &operator <<(ostream &ostr, Expression *expr)
{
    expr->operand(ostr);
    return ostr;
};

void Function::generate()
{
    Symbols tempSymbols =_body->declarations()->symbols();
    unsigned pSize = _id->type().parameters()->size();
    
    //Parameters
    int offset = 8;
    for(unsigned i = 0; i < pSize; ++i){
        tempSymbols[i]->_offset = offset;
        offset = offset + tempSymbols[i]->type().size();
    }
    
    //Declarations
    offset = 0;
    for (unsigned i = pSize; i < tempSymbols.size(); ++i) {
      offset = offset - tempSymbols[i]->type().size();
      tempSymbols[i]->_offset = offset;
    }
    
    //prologue
    cout << ".globl\t" << _id->name() << endl;
    cout << _id->name() << ":" << endl << "pushl\t%ebp" << endl;
    cout << "movl\t%esp, %ebp" << endl;
    cout << "subl\t$" << (offset * -1) << ", %esp" << endl;
    
    _body->generate();
    
    //epilouge
    cout << "movl\t%ebp, %esp" << endl;
    cout << "popl\t%ebp" << endl;
    cout << "ret" << endl;
}

void Block::generate(){
    for(auto stmt : _stmts){
        stmt->generate();
    }
}

void Simple::generate(){
    _expr->generate();
}

void Call::generate(){
    int temp = 0;
    for(int i = _args.size() - 1; i >= 0; --i){
        cout << "pushl\t" << _args[i] << endl;
        temp = temp + _args[i]->type().size();
    }

    cout << "call\t" << _id->name() << endl;
    cout << "addl\t$" << temp <<  ", %esp" << endl;
}

void Assignment::generate(){
    cout << "movl\t" << _right << ", " << _left <<endl;
}

void generateGlobals(Scope* outermost){
    for(auto symbol : outermost->symbols()){
        if(!symbol->type().isError() && !symbol->type().isFunction())
            cout << ".comm\t" << symbol->name() << ", " << symbol->type().size() << endl;
    }
}

void Identifier::operand(ostream &ostr) const{
    if(_symbol->_offset == 0)
        cout << _symbol->name();
    else
        cout << _symbol->_offset << "(%ebp)";
}

void Number::operand(ostream &ostr) const{
    ostr << "$" << _value;
}

void Expression::operand(ostream &ostr) const{
    
}
