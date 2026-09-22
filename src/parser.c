#include "error.h"
#include "node.h"
#include "symbol.h"
#include "token.h"

Scope cur_scope;

void parse_identifier(void) {
    //TODO do some research to see if we need to do anything else
    //cause present me cannot remember
    add_identifer(&cur_scope, token_view.token);
}   

void parse_statement(void) {
    

}

void parse_function(void) {
    //expect functions to start with an identifer
    if (token_view.is_match(IDENTIFIER)) {
        parse_identifier();
    } else {
        syntax_error(IDENTIFIER);
    }

    if (token_view.is_match(COLON)) {
        token_view.next_token();
        parse_statement();
    } else if (token_view.is_match(IDENTIFIER)) {
        parse_identifier();
    } else {
        syntax_error(IDENTIFIER);
    }
}

void parse_declaration(void) {
    if (token_view.is_match(FUNCTION)) {
        token_view.next_token();
        parse_function();
    } else {
        syntax_error(FUNCTION);
    }
}

void parse_block(void) {
    while (token_view.has_next()) {
        parse_declaration();
    }
}


Node* parser(void) {
    // do anything else
    //TODO setup symbol table
    cur_scope = (Scope) {
        NULL,
        NULL,
    };
    parse_block();
}


