#include "token.h"
#include <stdlib.h>
#include <string.h>


static inline void free_token(Token* token) {
    if (token == NULL) {
        return;
    }
    //TODO idk about freeing here, because these might be needed again later. 
    //TODO we might need a way to flag when to free 
    //if (token->value != NULL) {
    //    free(token->value);
    //}
    //if (token->loc != NULL) {
    //    free(token->loc);
    //}
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

static inline int has_next(void) {
    return token_view.token->next != NULL;
}

static inline int is_match(TokenType tt) {
    return tt == token_view.token->token_type;
}

/**
 * global TokenView so entire program can know where we are up to
 * token gets set at the start of the lexer.
 */
struct TokenView token_view = {
    .token = NULL,
    .next_token = next_token,
    .peek = peek,
    .has_next = has_next,
    .is_match = is_match,
};
