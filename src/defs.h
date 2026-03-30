#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    T_ADD,
    T_SUB,
    T_MULT,
    T_DIV,
    T_INTLIT,
    T_EOF,
} Token_t;

typedef enum {
    A_ADD,
    A_SUB,
    A_MULT,
    A_DIV,
    A_INTLIT
} AST_node_t;

// Lots to be learned from just one struct!
typedef struct AST_node {   // Struct tag - the compiler needs to resolve the left and right nodes.
    AST_node_t operator;
    struct AST_node *left;  // Left and right need to be pointer since a struct in C cannot
    struct AST_node *right; // contain itself. Using the struct keyword is important
                            // to let the compiler know we are reffering to a struct *tagged*
                            // AST_node, since the typedef has not yet been reached.
    int value;
} AST_node; // The alias created by typedefing this struct.

typedef struct {
    Token_t token_type;
    int value;
} Token;

#endif //DEFS_H