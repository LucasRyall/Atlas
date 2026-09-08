#include "lexer.h"
#include "token.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

void temp_print_tokens(void) {
    do {
        if(token_view.token->token_type == IDENTIFIER || token_view.token->token_type == NUMBER) {
            printf("%s\n", token_view.token->value);
        } else {
            printf("%s\n", token_strings[token_view.token->token_type]);
        }
    } while(token_view.next_token());
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Currently only taking in single files.\n");
        exit(1);
    }

    lexer(argv[1]);
    if (token_view.token->token_type == UNKNOWN) {
        fprintf(stderr, "Lexer Failed to make tokens");
        exit(1);
    }
    temp_print_tokens();
    //for(int i = 0; i < EOF_TOKEN; i++) {
    //    printf("%s\n", token_strings[i]);
    //}
}
