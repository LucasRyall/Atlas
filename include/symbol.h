

#ifndef SYMBOL
#define SYMBOL

#include "token.h"
#include <stddef.h>

typedef struct Scope {
    struct Scope* parent;
    struct SymbolMap* map;
    int level;

} Scope;

typedef struct Symbol {
    char* name;
    //TODO TYPE
} Symbol;

typedef struct SymbolMap {
    size_t capacity;
    size_t num_mem;
    struct Symbol** values;
} SymbolMap; 

Scope* init_scope(Scope* parent, int level);
int add_identifer(Scope* scope, Token* token);

#endif 

