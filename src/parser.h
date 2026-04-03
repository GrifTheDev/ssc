#ifndef PARSER_H
#define PARSER_H

#include "defs.h"

// Commenting out for now if needed later
/* AST_node *init_ast_node(AST_node_t operator_code, AST_node *left_node, AST_node *right_node, int node_value);
AST_node *create_ast_leaf(AST_node_t operator_code, int node_value);
AST_node *create_ast_unary(AST_node_t operator_code, AST_node *child_node, int node_value);
int translate_arithmetic_ops(Token_t token_t);
AST_node *build_primary(); */
void get_operator_precedence();
AST_node *parser_bin_exp(int p);
int interpret_AST(AST_node *current_node);


#endif // PARSER_h