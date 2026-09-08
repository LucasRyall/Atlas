#include "token.h"
#include <stdlib.h>
#include <string.h>


static inline void free_token(Token* token) {
    if (token == NULL) {
        return;
    }
    if (token->value != NULL) {
        free(token->value);
    }
    if (token->loc != NULL) {
        free(token->loc);
    }
    free(token);
}

static inline int next_token(void) {
    //might not be the safest thing ever. might want to change this in the future
    if(token_view.token->next == NULL) {
        return 0;
    }
    Token* prev = token_view.token;
    token_view.token = token_view.token->next;
    free_token(prev);
    return 1;
}


static inline TokenType peek(void) {
    return token_view.token->token_type;
}

static inline int is_match_kw(char* expected) {
    if (token_view.token->token_type != IDENTIFIER) {
        return 0;
    }
    if (strcmp(token_view.token->value, expected)) {
        return 0;
    } 
    return 1;
}

static inline int has_next(void) {
    return token_view.token->next != NULL;
}

/**
 * global TokenView so entire program can know where we are up to
 * token gets set at the start of the lexer.
 */
TokenView token_view = {
    .token = NULL,
    .next_token = next_token,
    .peek = peek,
    .has_next = has_next,
    .is_match_kw = is_match_kw,
};
