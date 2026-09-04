#define _GNU_SOURCE

#include <regex.h>
#include <string.h>
#include "lexer.h"
#include "token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


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
                token->token = PLUS;
                break;
            case '-':
                token->token = MINUS;
                break;
            case '*': 
                token->token = MULTIPLY;
                break;
            case '/':
                if (line[loc + 1] == '/') {
                    // this is a comment, will do to the end of line
                    return token;
                } else {
                    token->token = DIVIDE;
                }
                break;
            case '^':
                if (line[loc + 1] == '^') {
                    token->token = POWER;
                    loc++;
                } else {
                    skip = 1;
                    fprintf(stderr, "Bitwise operations not supported yet");
                }
                break;
            case ':': 
                token->token = COLON;
                break;
            case ';': 
                token->token = SEMICOLON;
                break;
            case '|': 
                token->token = PIPE;
                break;
            case ',': 
                token->token = COMMA;
                break;
            case '0' ... '9': {
                    regex_t reg;
                    regmatch_t match;
                    int rege = regcomp(&reg, "^[0-9]+\\.[0-9]+|^[0-9]+", REG_EXTENDED);
                    if (rege) {
                        fprintf(stderr, "Couldn't compile number regex.\n");
                        fprintf(stderr, "%s\n",line);
                        exit(rege);
                    }
                    rege = regexec(&reg, line+loc, 1, &match, 0);
                    if (rege) {
                        fprintf(stderr, "Failed regex on number.\n");
                        fprintf(stderr, "%s\n",line);
                        //probably dont want to exit on this? maybe we do idk
                    }
                    // +1 for null terminator
                    char* value = calloc(match.rm_eo + 1, sizeof(char));
                    snprintf(value, match.rm_eo+1, "%s", line+loc);
                    // -1 to accout for adding one again later
                    loc += match.rm_eo - 1;
                    token->value = value;
                    token->token = NUMBER;
                    regfree(&reg);
                    break;
                }
            case ' ': case '\t': case '\n': case '\r': case '\v': case '\f': 
                //dont care about whitespace
                skip = 1;
                break;
            case 'a' ... 'z': case 'A' ... 'Z': case '_': {
                    regex_t reg;
                    regmatch_t match;
                    int rege = regcomp(&reg, "[a-zA-Z][a-zA-Z0-9_]*", REG_EXTENDED);
                    if (rege) {
                        fprintf(stderr, "Couldn't compile itdentifer regex.\n");
                        fprintf(stderr, "%s\n",line);
                        exit(rege);
                    }
                    rege = regexec(&reg, line+loc, 1, &match, 0);
                    if (rege) {
                        fprintf(stderr, "Failed regex on identifier.\n");
                        fprintf(stderr, "%s\n",line);
                        //probably dont want to exit on this? maybe we do idk
                    }
                    // +1 for null terminator
                    char* value = calloc(match.rm_eo + 1, sizeof(char));
                    snprintf(value, match.rm_eo+1, "%s", line+loc);
                    // -1 to accout for adding one again later
                    loc += match.rm_eo - 1;
                    token->value = value;
                    token->token = IDENTIFIER;
                    regfree(&reg);
                    break;
                }
            default: 
                fprintf(stderr, "Bad symbol: %d, %c\n", line[loc], line[loc]); 
                fprintf(stderr, "%zu, %zu\n", location->line, location->column);
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
    token->token = EOF_TOKEN;

    if (line != NULL) {
        free(line);
    }
    fclose(file);
}
