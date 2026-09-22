
#ifndef ERROR
#define ERROR

#include "token.h"
#include <stdio.h>

struct Error {
    char** lines;
    int line_count;
};

extern struct Error error;

int get_line_count(FILE* file);

void lexer_error(Location* loc, char* msg, char unknown);

void syntax_error_single(TokenType expected);
void syntax_error_arr(TokenType* expected);

#define syntax_error(expected) \
    _Generic(expected, \
        int: syntax_error_single, \
        int*: syntax_error_arr \
    ) (expected);

#endif
