#ifndef AST
#define AST

#include "token.h"
typedef struct Tree {
    
} Tree;

typedef struct Node {
    
} Node;

typedef Node* (*TokenParser)(Token*);

static TokenParser token_parsers[] = {
    //[UNKNOWN]       = ,
    //[IDENTIFIER]    = ,
    //[NUMBER]        = ,
    // math operators
    //[PLUS]          = ,     //+
    //[MINUS]         = ,     //-
    //[MULTIPLY]      = ,     //*
    //[DIVIDE]        = ,     ///
    //[POWER]         = ,     //^^
    //    = logical operators
    //[OR]            = ,     //||
    //[AND]           = ,     //&&
    //[NOT]           = ,     //!!
    //[EQUALS]        = ,     //==
    //[NOTEQUALS]     = ,     //!=
    //    = other symbols
    //[COLON]         = ,
    //[SEMICOLON]     = ,
    //[PIPE]          = ,     //|
    //[COMMA]         = ,
    //[PERIOD]        = ,
    //[EOF_TOKEN]     = ,
};


#endif
