/*
 * File:	checker.h
 */

# ifndef CHECKER_H
# define CHECKER_H
# include "type.h"

typedef std::string string;

void openScope();
void closeScope();
void declareVariable(const string &name, const Type &_type);
void declareFunction(const string &name, const Type &_type);
void defineFunction(const string &name, const Type &_type);
void checkID(const string &name);

# endif /* CHECKER_H */
