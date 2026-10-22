#ifndef NODE
#define NODE

#include "token.h"
#include "util/dynamic_array.h"


typedef struct Node {
    Location* loc;
    
} Node;

typedef struct IdentiferNode {
    Node* node;
    char* name;
    //Type type;
} IdentiferNode;

typedef struct StatementNode {
    Node* node;

} StatementNode;

typedef struct FunctionNode {
    Node* node;
    //Identifer_Nodes, maybe?
    DynamicArray* arguments;

} FunctionNode;


#endif
