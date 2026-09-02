#ifndef TOKEN
#define TOKEN

#include <stddef.h>


typedef enum {
    UNKNOWN,
    IDENTIFIER,
    NUMBER,
    //math operators
    PLUS,       //+
    MINUS,      //-
    MULTIPLY,   //*
    DIVIDE,     ///
    POWER,      //^^
    //logical operators
    OR,         //||
    AND,        //&&
    NOT,        //!!
    EQUALS,     //==
    NOTEQUALS,  //!=
    //other symbols
    COLON,
    ASSIGNMENT, //:= idk if this is even needed
    COMMA,
    PERIOD,
    EOF_TOKEN,
} TokenType;

typedef struct Location {
    size_t line;
    size_t column;
} Location;

typedef struct Token {
    char* value; //probably only used for identifers
    TokenType token;
    struct Token* next;
    Location loc;
} Token;

Token* next_token (Token token);

#endif
