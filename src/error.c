
#include "token.h"
#include "error.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int get_line_count(FILE* file) {
    size_t buf_size = 65536;
    char buf[buf_size];
    int line_counter = 0;
    while(!feof(file)) {
        size_t read_count = fread(buf, 1, buf_size, file);
        if (ferror(file)) {
            return -1;
        }

        for (size_t i = 0; i < read_count; i++) {
            if (buf[i] == '\n') {
                line_counter++;
            }
        }
    }
    fseek(file, 0, SEEK_SET);
    return line_counter;
}

extern inline void lexer_error(Location* loc, char* msg, char unknown) {
    fprintf(stderr, "Lexer Error (%zu, %zu): %s: %c\n", loc->line, loc->column, msg, unknown);
    fprintf(stderr, "%s", error.lines[loc->line]);
    fprintf(stderr, "%*s^\n", (int) loc->column, " ");
}

extern inline void syntax_error_single(TokenType expected) {
    fprintf(stderr, "Syntax Error (%zu, %zu): Expected %s, Found %s\n",
            token_view.token->loc->line, token_view.token->loc->column,
            token_strings[expected], token_strings[token_view.token->token_type]);
    fprintf(stderr, "%s", error.lines[token_view.token->loc->line]);
    fprintf(stderr, "%*s^\n", (int) token_view.token->loc->column, " ");
}

struct Error error = {
    .lines = NULL,
    .line_count = 0,
};


