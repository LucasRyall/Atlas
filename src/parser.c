
#include "ast.h"
#include "token.h"

void parse_identifier(void) {

}

void parse_block(void) {
    parse_identifier();
}


Tree* parser(void) {
    // do anything else
    //TODO setup symbol table
    parse_block();
}


