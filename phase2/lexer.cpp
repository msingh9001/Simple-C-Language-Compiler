/*
 * File:	lexer.cpp
 *
 * Description:	This file contains the public and private function and
 *		variable definitions for the lexical analyzer for Simple C.
 *
 *		Extra functionality:
 *		- checking for out of range integer literals
 *		- checking for invalid string literals
 */

# include <set>
# include <cstdio>
# include <cerrno>
# include <cctype>
# include <cstdlib>
# include <iostream>
# include <map>
# include <iterator>
# include "string.h"
# include "lexer.h"
# include "tokens.h"

using namespace std;
int numerrors, lineno = 1;


/* Later, we will associate token values with each keyword */

static set<string> keywords = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while",
};


/*
 * Function:	report
 *
 * Description:	Report an error to the standard error prefixed with the
 *		line number.  We'll be using this a lot later with an
 *		optional string argument, but C++'s stupid streams don't do
 *		positional arguments, so we actually resort to snprintf.
 *		You just can't beat C for doing things down and dirty.
 */

void report(const string &str, const string &arg)
{
    char buf[1000];

    snprintf(buf, sizeof(buf), str.c_str(), arg.c_str());
    cerr << "line " << lineno << ": " << buf << endl;
    numerrors ++;
}


/*
 * Function:	lexan
 *
 * Description:	Read and tokenize the standard input stream.  The lexeme is
 *		stored in a buffer.
 */

int lexan(string &lexbuf)
{
    static int c = cin.get();
    bool invalid, overflow;
    long val;
    int p;

    static map<std::string, int> m {
        {"auto", 256},
        {"break", 257},
        {"case", 258},
        {"char", 259},
        {"const", 260},
        {"continue", 261},
        {"default", 262},
        {"do", 263},
        {"double", 264},
        {"else", 265},
        {"enum", 266},
        {"extern", 267},
        {"float", 268},
        {"for", 269},
        {"goto", 270},
        {"if", 271},
        {"int", 272},
        {"long", 273},
        {"register", 274},
        {"return", 275},
        {"short", 276},
        {"signed", 277},
        {"sizeof", 278},
        {"static", 279},
        {"struct", 280},
        {"switch", 281},
        {"typedef", 282},
        {"union", 283},
        {"unsigned", 284},
        {"void", 285},
        {"volatile", 286},
        {"while", 287},
    };


    /* The invariant here is that the next character has already been read
       and is ready to be classified.  In this way, we eliminate having to
       push back characters onto the stream, merely to read them again. */

    while (!cin.eof()) {
        lexbuf.clear();
        
        
        /* Ignore white space */
        
        while (isspace(c)) {
            if (c == '\n')
                lineno ++;
            
            c = cin.get();
        }
        
        
        /* Check for an identifier or a keyword */
        
        if (isalpha(c) || c == '_') {
            do {
                lexbuf += c;
                c = cin.get();
            } while (isalnum(c) || c == '_');
            
            if (keywords.count(lexbuf) > 0){
                return m[lexbuf];
            }else
                return ID;
            
            
            /* Check for a number */
            
        } else if (isdigit(c)) {
            do {
                lexbuf += c;
                c = cin.get();
            } while (isdigit(c));
            
            errno = 0;
            val = strtol(lexbuf.c_str(), NULL, 0);
            
            if (errno != 0 || val != (int) val)
                report("integer constant too large");
            
            return NUM;
            
            
            /* There must be an easier way to do this.  It might seem stupid at
             this point to recognize each token separately, but eventually
             we'll be returning separate token values to the parser, so we
             might as well do it now. */
            
        } else {
            lexbuf += c;
            
            switch(c) {
                    
                    
                    /* Check for '||' */
                    
                case '|':
                    c = cin.get();
                    
                    if (c == '|') {
                        lexbuf += c;
                        c = cin.get();
                        return OR;
                    }
                    
                    return ABS_VAL;
                    
                    
                    /* Check for '=' and '==' */
                    
                case '=':
                    c = cin.get();
                    
                    if (c == '=') {
                        lexbuf += c;
                        c = cin.get();
                        return EQUAL;
                    }
                    
                    return ASSIGN;
                    
                    
                    /* Check for '&' and '&&' */
                    
                case '&':
                    c = cin.get();
                    
                    if (c == '&') {
                        lexbuf += c;
                        c = cin.get();
                        return AND;
                    }
                    
                    return ADDR;
                    
                    
                    /* Check for '!' and '!=' */
                    
                case '!':
                    c = cin.get();
                    
                    if (c == '=') {
                        lexbuf += c;
                        c = cin.get();
                        return NOT_EQUAL;
                    }
                    
                    return NOT;
                    
                    
                    /* Check for '<' and '<=' */
                    
                case '<':
                    c = cin.get();
                    
                    if (c == '=') {
                        lexbuf += c;
                        c = cin.get();
                        return LESS_THAN_OR_EQUAL_TO;
                    }
                    
                    return LESS_THAN;
                    
                    
                    /* Check for '>' and '>=' */
                    
                case '>':
                    c = cin.get();
                    
                    if (c == '=') {
                        lexbuf += c;
                        c = cin.get();
                        return GREATER_THAN_OR_EQUAL_TO;
                    }
                    
                    return GREATER_THAN;
                    
                    
                    /* Check for '-', '--', and '->' */
                    
                case '-':
                    c = cin.get();
                    
                    if (c == '-') {
                        lexbuf += c;
                        c = cin.get();
                        return DECREMENT;
                    } else if (c == '>') {
                        lexbuf += c;
                        c = cin.get();
                        return POINTS_TO;
                    }
                    
                    return SUB;
                    
                    
                    /* Check for '+' and '++' */
                    
                case '+':
                    c = cin.get();
                    
                    if (c == '+') {
                        lexbuf += c;
                        c = cin.get();
                        return INCREMENT;
                    }
                    
                    return ADD;
                    
                    
                    /* Check for simple, single character tokens */
                    
                case '*':
                    c = cin.get();
                    return '*';
                    
                case '%':
                    c = cin.get();
                    return '%';
                
                case ':':
                    c = cin.get();
                    return ':';
                
                case ';':
                    c = cin.get();
                    return ';';
                
                case '(':
                    c = cin.get();
                    return '(';
                
                case ')':
                    c = cin.get();
                    return ')';
                
                case '[':
                    c = cin.get();
                    return '[';
                
                case ']':
                    c = cin.get();
                    return ']';
                
                case '{':
                    c = cin.get();
                    return '{';
                
                case '}':
                    c = cin.get();
                    return '}';
                
                case '.':
                    c = cin.get();
                    return '.';
                
                case ',':
                    c = cin.get();
                    return ',';
                    
                    
                    
                    /* Check for '/' or a comment */
                    
                case '/':
                    c = cin.get();
                    
                    if (c == '*') {
                        do {
                            while (c != '*' && !cin.eof()) {
                                if (c == '\n')
                                    lineno ++;
                                
                                c = cin.get();
                            }
                            
                            c = cin.get();
                        } while (c != '/' && !cin.eof());
                        
                        c = cin.get();
                        break;
                        
                    } else {
                        return '/';
                    }
                    
                    
                    /* Check for a string literal */
                    
                case '"':
                    do {
                        p = c;
                        c = cin.get();
                        lexbuf += c;
                        
                        if (c == '\n')
                            lineno ++;
                        
                    } while (p == '\\' || (c != '"' && c != '\n' && !cin.eof()));
                    
                    if (c == '\n' || cin.eof())
                        report("premature end of string literal");
                    else {
                        parseString(lexbuf, invalid, overflow);
                        
                        if (invalid)
                            report("unknown escape sequence in string literal");
                        else if (overflow)
                            report("escape sequence out of range in string literal");
                    }
                    
                    c = cin.get();
                    return STRING;
                    
                    
                    /* Handle EOF here as well */
                    
                case EOF:
                    return DONE;
                    
                    
                    /* Everything else is illegal */
                    
                default:
                    c = cin.get();
                    break;
            }
        }
    }
    return -1;
}
