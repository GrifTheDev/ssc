#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// Pursuant to https://www.rfc-editor.org/rfc/rfc5424#section-6.2.1 Table 2
// Labeled integers for easier integration in if/else and switch statements.
typedef enum {
    SSC_EMERGENCY = 0, // system is unusable
    SSC_ALERT =     1, // action must be taken immediately
    SSC_CRITICAL =  2, // critical conditions
    SSC_ERROR =     3, // error conditions
    SSC_WARNING =   4, // warning conditions
    SSC_NOTICE =    5, // normal but significant condition
    SSC_INFO =      6, // informational messages
    SSC_DEBUG =     7  // debug-level messages 
} SSC_LogLevel;

typedef enum {
    T_EOF,
    T_ADD,
    T_SUB,
    T_MULT,
    T_DIV,
    T_INTLIT,
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