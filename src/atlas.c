#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void temp_print_tokens(void) {
    do {
        if(token_view.token->token_type == IDENTIFIER || token_view.token->token_type == NUMBER) {
            printf("%s\n", token_view.token->value);
        } else {
            printf("%s\n", token_strings[token_view.token->token_type]);
        }
        if (token_view.is_match(EOF_TOKEN)){
            break;
        }
    } while(token_view.next_token());
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Currently only taking in single files.\n");
        exit(1);
    }

    FILE* file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Couldn't open file");
        exit(1);
    }
    
    int line_count = get_line_count(file);
    error.lines = calloc(line_count, sizeof(char*));
    error.line_count = line_count;

    lexer(file);

    fclose(file);

    if (token_view.token->token_type == UNKNOWN) {
        fprintf(stderr, "Lexer Failed to make tokens");
        exit(1);
    }

    parser();

    return 0;
}
