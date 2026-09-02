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
    SEMICOLON,
    PIPE,       //|
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

typedef struct TokenView {
    Token* token;
    int (*next_token)(void);
} TokenView;

extern TokenView token_view;

int next_token(void);

#endif
