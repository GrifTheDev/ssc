#include "defs.h"
#include "data.h"
#include "lexer.h"

static AST_node *init_ast_node(AST_node_t operator_code, AST_node *left_node, AST_node *right_node, int node_value) {
    AST_node *output;

    // Allocating memory on the heap for our node since we need it outside of the scope of this function.
    // TODO: when do we free this?
    output = malloc(sizeof(AST_node));
    if (output == NULL) {
        printf("[PARSER] [ERR] Could not allocate memory on the heap for an AST node.\n");
        exit(1);
    }

    output->operator = operator_code;
    output->left = left_node;
    output->right = right_node;
    output->value = node_value;

    return output;
}

static AST_node *create_ast_leaf(AST_node_t operator_code, int node_value) {
    return init_ast_node(operator_code, NULL, NULL, node_value);
}

static AST_node *create_ast_unary(AST_node_t operator_code, AST_node *child_node, int node_value) {
    return init_ast_node(operator_code, child_node, NULL, node_value);
}

static int translate_arithmetic_ops(Token_t token_t) {
    switch (token_t) {
        case T_ADD:
            return A_ADD;
            break;
        case T_SUB:
            return A_SUB;
            break;
        case T_MULT:
            return A_MULT;
            break;
        case T_DIV:
            return A_DIV;
            break;
        default:
            printf("unknown token in arithmetic lex to ast translation unit %d\n", token_t);
            exit(1);
    }
}

// Checks to see if the current token is a primary aka an operand, and return it as a node (no children)
static AST_node *build_primary() {
    //AST_node *output;

    switch(current_token.token_type) {
        case T_INTLIT:
            return create_ast_leaf(A_INTLIT, current_token.value);
            break;
        default:
            printf("[ERR] Syntax error on line %d\n", line_number);
            exit(1);
    }
}

// Build a tree out of an input of binary expression tokens recursivelly, the root must be an arithmetic operator
AST_node *parser_bin_exp() {
    AST_node *left_node, *right_node;
    AST_node_t node_type;

    // Unlike the tutorial I've decided to offload the scanning in of new lexical token to here for now
    lexer_next_token();
    // Due to the grammar of our language, I am assuming the first token will be an T_INTLIT
    left_node = build_primary();

    lexer_next_token();
    if (current_token.token_type == T_EOF) return left_node; // Recursion break
    node_type = translate_arithmetic_ops(current_token.token_type); // ? Could this be done with no parameter, just referencing the current token from data.h?

    right_node = parser_bin_exp();
    
    return init_ast_node(node_type, left_node, right_node, 0);
}

// In-order binary tree traversal
int interpret_AST(AST_node *current_node) {
    int left_val, right_val;

    if (current_node->left) left_val = interpret_AST(current_node->left);
    if (current_node->right) right_val = interpret_AST(current_node->right);

    switch(current_node->operator) {
        case A_ADD:
            printf("add: %d + %d\n", left_val, right_val);
            return left_val + right_val;
        case A_SUB:
            printf("sub: %d - %d\n", left_val, right_val);
            return left_val - right_val;
        case A_MULT:
            printf("mult: %d * %d\n", left_val, right_val);
            return left_val * right_val;
        case A_DIV:
            printf("div: %d / %d\n", left_val, right_val);
            return left_val / right_val;
        case A_INTLIT:
            printf("int %d\n", current_node->value);
            return current_node->value;
        default:
            printf("unknown operator encountered %d\n", current_node->operator);
            exit(1);
    }
}