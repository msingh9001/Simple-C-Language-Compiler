/*
 * File:	tokens.h
 *
 * Description:	This file contains the token definitions for use by the
 *		lexical analyzer and parser for Simple C.  Single character
 *		tokens use their ASCII values, so we can refer to them
 *		either as character literals or as symbolic names.
 */

# ifndef TOKENS_H
# define TOKENS_H

enum {
    // single character operators
    ASSIGN = '=', SUB = '-', ADD = '+', GREATER_THAN = '>', LESS_THAN = '<', MOD = '%', DIV = '/', MUL = '*', NOT = '!', ADDR = '&', OPEN_BRACKET = '[', CLOSE_BRACKET =']', OPEN_P = '(', CLOSE_P = ')', COLON = ':', SEMI_COLON = ';', OPEN_CURLY_BRACKET = '{', CLOSE_CURLY_BRACKET = '}', ABS_VAL = '|', COMMA = ',', POINTER = '*', NEG = '-',  /* . . . */

    // keywords
    AUTO = 256, BREAK = 257, CASE = 258, CHAR = 259, CONST = 260, CONTINUE = 261, DEFAULT = 262, DO = 263, DOUBLE = 264, ELSE = 265, ENUM = 266, EXTERN = 267, FLOAT = 268, FOR = 269, GOTO = 270, IF = 271, INT = 272, LONG = 273, REGISTER = 274, RETURN = 275, SHORT = 276, SIGNED = 277, SIZEOF = 278, STATIC = 279, STRUCT = 280, SWITCH = 281, TYPEDEF = 282, UNION = 283, UNSIGNED = 284, VOID = 285, VOLATILE = 286, WHILE = 287,

    // two character operators, ID, num, string, done
    OR = 288, AND = 289, EQUAL = 290, NOT_EQUAL = 291, LESS_THAN_OR_EQUAL_TO = 292, GREATER_THAN_OR_EQUAL_TO = 293, INCREMENT = 294, DECREMENT = 295, POINTS_TO = 296, ID = 297, NUM = 298, STRING = 299, DONE = 300,

};

# endif /* TOKENS_H */
