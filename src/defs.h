#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>

typedef enum {
    T_ADD,
    T_SUB,
    T_MULT,
    T_DIV,
    T_INTLIT
} Token_t;

typedef struct {
    Token_t token_type;
    int value;
} Token;

#endif //DEFS_H