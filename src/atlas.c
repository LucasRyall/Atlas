#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Currently only taking in single files.\n");
        exit(1);
    }

    lexer(argv[1]);
    if (token_view.token->token == UNKNOWN) {
        fprintf(stderr, "Lexer Failed to make tokens");
        exit(1);
    }
    do {
        if(token_view.token->value != NULL) {
            printf("%s\n", token_view.token->value);
        }  
    } while(token_view.next_token());
    printf("\n");
}
