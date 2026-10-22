
#include "symbol.h"
#include "token.h"
#include <stdlib.h>
#include <string.h>

/**
 * hashes variable identifers for our table. 
 * should work fine enough for this project
 * function comes from: http://www.cse.yorku.ca/~oz/hash.html 
 */
size_t hash(char* str, size_t capacity) {
    size_t hash = 5381;

    size_t c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) ^ c;
    }
        
    return hash % capacity;
}

/**
 * doubles the capacity of the map, and redistributes values
 */
void add_capacity(SymbolMap* map) {
    size_t old_capacity = map->capacity;
    map->capacity = old_capacity*2;

    Symbol** old_arr = map->values;
    map->values = calloc(map->capacity, sizeof(Symbol*));

    for(size_t i = 0; i < old_capacity; i++) {
        if (old_arr[i] == NULL) {
            continue;
        }
        map->values[hash(old_arr[i]->name, map->capacity)] = old_arr[i];
    }
    free(old_arr);
}


Scope* init_scope(Scope* parent, int level) {
    SymbolMap* map = malloc(sizeof(SymbolMap));
    map->capacity = 2;
    map->num_mem = 0;
    map->values = calloc(map->capacity, sizeof(Symbol*));

    Scope* scope = malloc(sizeof(Scope));
    scope->parent = parent;
    scope->map = map;
    scope->level = level;

    return scope;
}

int add_identifer(Scope* scope, Token* token) {
    SymbolMap* map = scope->map;
    
    if (map->num_mem != 0 && map->capacity / map->num_mem == 1) {
        add_capacity(map);
    }

    size_t i = hash(token->value, map->capacity);

    if (map->values[i]) {
        if (!strcmp(map->values[i]->name, token->value)) {
            //duplicate value
            //TODO not sure if we want to anything here?
            //
            return 1;
        }
        while(map->values[i]) {
            i++;
        }
    }
    Symbol* sym = malloc(sizeof(Symbol));
    map->values[i] = sym;
    sym->name = token->value;
    return 0;
}

