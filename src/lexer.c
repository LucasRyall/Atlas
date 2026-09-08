#define _GNU_SOURCE

#include <regex.h>
#include <string.h>
#include "lexer.h"
#include "token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int handle_long_symbol(Token* token, char* regex, char* line, int loc) {
    regex_t reg;
    regmatch_t match;
    int rege = regcomp(&reg, regex, REG_EXTENDED);
    if (rege) {
        fprintf(stderr, "Couldn't compile regex.\n");
        fprintf(stderr, "%s\n",line);
        exit(rege);
    }
    rege = regexec(&reg, line+loc, 1, &match, 0);
    if (rege) {
        fprintf(stderr, "Failed regex on number.\n");
        fprintf(stderr, "%s\n",line);
        //probably dont want to exit on this? maybe we do idk
    }
    regfree(&reg);
    // +1 for null terminator
    char* value = calloc(match.rm_eo + 1, sizeof(char));
    snprintf(value, match.rm_eo+1, "%s", line+loc);
    // -1 to accout for adding one again later
    token->value = value;
    return loc + match.rm_eo - 1;
}

/**
 * line:        current line we are working on
 * line_length: length of the current line
 * loc:         where we are in the line  
 * token:       current token
 */
Token* match_token(char* line, size_t line_l, size_t line_n, Token* token) {
    size_t loc = 0;
    while (loc < line_l) {
        Location* location = malloc(sizeof(Location));
        location->line = line_n;
        location->column = loc;
        token->loc = location;
        char curr = line[loc];
        int skip = 0;
        switch (curr) {
            case '+': 
                token->token_type = PLUS;
                break;
            case '-':
                if (line[loc + 1] == '>') {
                    token->token_type = ARROW;
                } else {
                    token->token_type = MINUS;
                }
                break;
            case '*': 
                token->token_type = MULTIPLY;
                break;
            case '/':
                if (line[loc + 1] == '/') {
                    // this is a comment, will do to the end of line
                    return token;
                } else {
                    token->token_type = DIVIDE;
                }
                break;
            case '^':
                if (line[loc + 1] == '^') {
                    token->token_type = POWER;
                    loc++;
                } else {
                    skip = 1;
                    fprintf(stderr, "Bitwise operations not supported yet");
                }
                break;
            case ':': 
                token->token_type = COLON;
                break;
            case ';': 
                token->token_type = SEMICOLON;
                break;
            case '|': 
                token->token_type = PIPE;
                break;
            case ',': 
                token->token_type = COMMA;
                break;
            case '0' ... '9': {
                    loc = handle_long_symbol(token, "^[0-9]+\\.[0-9]+|^[0-9]+", line, loc);
                    token->token_type = NUMBER;
                    break;
                }
            case ' ': case '\t': case '\n': case '\r': case '\v': case '\f': 
                //dont care about whitespace
                skip = 1;
                break;
            case 'a' ... 'z': case 'A' ... 'Z': case '_': {
                    loc = handle_long_symbol(token, "[a-zA-Z_][a-zA-Z0-9_]*", line, loc);
                    // not really a better way sadly
                    if (!strcmp(token->value, "fn")) {
                        free(token->value);
                        token->value = NULL;
                        token->token_type = FUNCTION;
                    } else if (!strcmp(token->value, "if")) {
                        free(token->value);
                        token->value = NULL;
                        token->token_type = IF;
                    } else if (!strcmp(token->value, "then")) {
                        free(token->value);
                        token->value = NULL;
                        token->token_type = THEN;
                    } else if (!strcmp(token->value, "else")) {
                        free(token->value);
                        token->value = NULL;
                        token->token_type = ELSE;
                    } else if (!strcmp(token->value, "const")) {
                        free(token->value);
                        token->value = NULL;
                        token->token_type = CONST;
                    } else if (!strcmp(token->value, "include")) {
                        free(token->value);
                        token->value = NULL;
                        token->token_type = INCLUDE;
                    } else {
                        token->token_type = IDENTIFIER;
                    }
                    break;
                }
            default: 
                fprintf(stderr, "Unknown symbol: %d, %c\n", line[loc], line[loc]); 
                fprintf(stderr, "Location: %zu, %zu\n", location->line, location->column);
                fprintf(stderr, "If this is where an identifier is supposed to be, identifers can only start with alpha charaters or '_', and files are expected to be UTF-8 encoded.\n");
                fprintf(stderr, "Unkown symbol has been skipped and compiler will attempt to continue.\n");
                skip = 1;
                break;
            
        }
        loc++;
        if (!skip) {
            Token* new_token = malloc(sizeof(Token));
            new_token->value = NULL;
            token->next = new_token;
            token = new_token;
        }
    }
    return token;
}


/**
 *  takes input file and outputs an array of tokens
 */
void lexer(char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror("Couldn't open file");
        exit(1);
    }
    
    Token* token = malloc(sizeof(Token));
    token->value = NULL;
    token_view.token = token;
    char* line = NULL;
    size_t line_length = 0;
    size_t line_n = 0;
    while(getline(&line, &line_length, file) >= 0) {
        token = match_token(line, strlen(line), line_n, token);
        line_n++;
    }
    //this one should always be the eof token.. maybe
    token->token_type = EOF_TOKEN;

    if (line != NULL) {
        free(line);
    }
    fclose(file);
}
