#include "token.h"


int next_token(void) {
    if(token_view.token->next == NULL) {
        return 0;
    }
    token_view.token = token_view.token->next;
    return 1;
}
