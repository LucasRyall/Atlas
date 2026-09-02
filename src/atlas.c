#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Currently only taking in single files.\n");
        exit(1);
    }

    Token* token = lexer(argv[1]);
    if (token->token == 0) {
        fprintf(stderr, "Lexer Failed to make tokens");
        exit(1);
    }
    int end = 0;
    while (!end) {
        switch (token->token) {
            case IDENTIFIER: case NUMBER:
                printf("%s", token->value);
                break;
            case PLUS:
                printf("+");
                break;
            case MINUS:
                printf("-");
                break;
            case MULTIPLY:
                printf("*");
                break;
            case DIVIDE:
                printf("/");
                break;
            case POWER:
                printf("^^");
                break;
            case COLON:
                printf(":");
                break;
            case COMMA:
                printf(",");
                break;
            case EOF_TOKEN:
                end = 1;
                break;
            default:
                printf("_");
        }
        token = token->next;
    }
    printf("\n");
}
