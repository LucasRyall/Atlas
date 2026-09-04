#ifndef TOKEN
#define TOKEN

//define sets
#define EXPR_START_SET 1<<0
#define UNARY_OP 1<<1
#define BINARY_OP 1<<2
#define RELATIONAL_OP 1<<3


#define TOKEN_TYPES \
    X(UNKNOWN, 0) \
    X(IDENTIFIER, EXPR_START_SET) \
    X(NUMBER, EXPR_START_SET) \
    X(PLUS, BINARY_OP) \
    X(MINUS, UNARY_OP | BINARY_OP) \
    X(MULTIPLY, BINARY_OP) \
    X(DIVIDE, BINARY_OP) \
    X(POWER, BINARY_OP) \
    X(OR, RELATIONAL_OP) \
    X(AND, RELATIONAL_OP) \
    X(NOT, RELATIONAL_OP) \
    X(EQUALS, RELATIONAL_OP) \
    X(NOTEQUALS, RELATIONAL_OP) \
    X(COLON, 0) \
    X(SEMICOLON, 0) \
    X(PIPE, 0) \
    X(COMMA, 0) \
    X(PERIOD, 0) \
    X(EOF_TOKEN, 0)
#include <stddef.h>

//typedef enum TokenType {
//    UNKNOWN,
//    IDENTIFIER,
//    NUMBER,
//    //math operators
//    PLUS,       //+
//    MINUS,      //-
//    MULTIPLY,   //*
//    DIVIDE,     ///
//    POWER,      //^^
//    //logical operators
//    OR,         //||
//    AND,        //&&
//    NOT,        //!!
//    EQUALS,     //==
//    NOTEQUALS,  //!=
//    //other symbols
//    COLON,
//    SEMICOLON,
//    PIPE,       //|
//    COMMA,
//    PERIOD,
//    EOF_TOKEN,
//} TokenType;
//
#define X(name, sets) name,
typedef enum { TOKEN_TYPES } TokenType;
#undef X

#define X(name, sets) [name] = (sets),
static const int token_sets[] = { TOKEN_TYPES };
#undef X

typedef struct Location {
    size_t line;
    size_t column;
} Location;

typedef struct Token {
    char* value; //probably only used for identifers
    TokenType token;
    struct Token* next;
    Location* loc;
} Token;

typedef struct TokenView {
    Token* token;
    int (*next_token)(void);
    TokenType (*peek)(void);
    int (*has_next)(void);
} TokenView;

extern TokenView token_view;

//int next_token(void);
//TokenType peek(void);
//int has_next(void);

#endif
