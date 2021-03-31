/*
 * File:	type.h
 */

# ifndef TYPE_H
# define TYPE_H
# include <vector>
# include <ostream>

typedef std::vector<class Type> Parameters;

class Type{
    int specifier;
    unsigned indirection;
    unsigned length;
    Parameters *parameters; //nullptr = (), [] = (void)
    
    enum { ARRAY, ERROR, FUNCTION, SCALAR } _kind;
    
public:
    Type();
    Type(int thisSpecifier, unsigned thisIndirection);
    Type(int thisSpecifier, unsigned thisIndirection, unsigned thisLength);
    Type(int thisSpecifier, unsigned thisIndirection, Parameters *theseParameters);
    
    bool isArray() const{ return _kind == ARRAY; };
    bool isError() const{ return _kind == ERROR; };
    bool isFunction() const{ return _kind == FUNCTION; };
    bool isScalar() const{ return _kind == SCALAR; };
    
    int _specifier() const { return specifier; };
    unsigned _indirection() const { return indirection; };
    unsigned _length() const { return length; };
    Parameters *_parameters() const{ return parameters; };
    
    bool operator == (const Type &rhs) const;
    bool operator != (const Type &rhs) const;
};
/*
std::ostream &operator <<(std::ostream &ostr, const Type &type){ ostr << type->specifier << type->indirection << type->length << type->parameters; return ostr; };
 */
# endif /* TYPE_H */
