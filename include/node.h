#ifndef NODE
#define NODE

#include "token.h"


typedef struct Node {
    Location* loc;
    
} Node;

typedef struct Identifer_Node {
    Node* node;
    char* name;
    //Type type;
} Identifer_Node;

typedef struct Statement_Node {
    Node* node;

} Statement_Node;

typedef struct Function_Node {
    Node* node;
    Identifer_Node** arguments;

} Function_Node;


#endif
