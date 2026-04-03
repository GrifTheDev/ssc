#include "defs.h"
#include "data.h"

#include "utils.h"
#include "lexer.h"

static AST_node *init_ast_node(AST_node_t operator_code, AST_node *left_node, AST_node *right_node, int node_value) {
    AST_node *output;

    // Allocating memory on the heap for our node since we need it outside of the scope of this function.
    // TODO: when do we free this?
    output = malloc(sizeof(AST_node));
    if (output == NULL) {
        ssc_message(SSC_EMERGENCY, "Could not allocate memory on the heap for an AST node", "");
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
            ssc_message(SSC_EMERGENCY, "Could not translate token '%d' into an AST node type\n", token_t);
            return 1; // This will never be reached, ssc_message will call exit(1)
            break;
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
            ssc_message(SSC_ERROR, "%d:%d | Syntax error\n", line_number, col_number);
            return create_ast_leaf(A_INTLIT, 69); // This will never be reached, ssc_message will call exit(1)
            break;
    }
}

/*
    (01/04/2026): We are defining a static table to resolve precedence issues with the Pratt Parser implementation.
    I am a bit sceptical of this approach since it does work with the simple case of having just a
    math expression language, but what about when we add more token types in Token_t. Since this is
    just accessing an array, we made it so the indecies correspond to the enum decleration. So if we
    shift things around in the Token_t enum, this table will not be valid. I am writing this comment on
    a ship with shotty wifi, so I cannot google solutions for this just yet, but I'll keep this comment
    here as a reminder of the issue.
*/
static int operator_precedence[] = { 0 , 10, 10, 20, 20,   0   };
//                                  EOF  +   -   *   /   intlit

int get_operator_precedence() {
    #ifdef _
        char *tok_lookup[] = { "EOF", "+", "-", "*", "/", "intlit"};
        ssc_message(SSC_DEBUG, "Operator precedence values:\n", "");
        
        for (int i = 0; i < 6; i++) {
            ssc_message(SSC_DEBUG, "  %s = %d\n", tok_lookup[i], operator_precedence[i]);
        }
    #endif // DEV

    int current_precedence = operator_precedence[current_token.token_type];
    if (current_precedence == 0) {
        // As explained in acwj 234 101 is not grammatically correct, this check enforces that
        ssc_message(SSC_DEBUG, "%d:%d | Syntax error: current_precedence = 0, current_token.type = %d\n", line_number, col_number, current_token.token_type);
        ssc_message(SSC_ERROR, "%d:%d | Syntax error: integer literal must be followed by an operator\n", line_number, col_number);
        return 1; // unreachable
    }

    return current_precedence;
}

// Build a tree out of an input of binary expression tokens recursivelly, the root must be an arithmetic operator
AST_node *parser_bin_exp(int p) {
    AST_node *left_node, *right_node;
    AST_node_t node_type;

    // Unlike the tutorial I've decided to offload the scanning in of new lexical token to here for now
    // Due to the grammar of our language, assumes the first token will be an T_INTLIT
    left_node = build_primary();
    lexer_next_token();
    
    if (current_token.token_type == T_EOF) return left_node; // Recursion break
    
    while (get_operator_precedence() > p) {
        /*
            (03/04/2026) This was an important addition not mentioned in the original acwj (or maybe I'm just dumb and can't read).
            Basically, when we advance the token in main we start at the number, then we advance it here after building a primary,
            and then we advance it again in the loop causing us to end up on a number. But we can't advance until we've processed
            the current operator and had it "ask" the next one: "hey, is this my right hand argument or your left hand one?". So we
            save the state of the current token, both it's type and precedence and start the recursive call with those. We can then
            safely advance to the next token, a number, and continue evaluating recursively from there.
        */
        int local_token_type = current_token.token_type;
        int local_token_prec = get_operator_precedence();
        lexer_next_token();

        right_node = parser_bin_exp(local_token_prec);

        node_type = translate_arithmetic_ops(local_token_type);
        left_node = init_ast_node(node_type, left_node, right_node, 0);

        if (current_token.token_type == T_EOF) return left_node;
    }
    
    return left_node;
}

// In-order binary tree traversal
int interpret_AST(AST_node *current_node) {
    int left_val, right_val;

    if (current_node->left) left_val = interpret_AST(current_node->left);
    if (current_node->right) right_val = interpret_AST(current_node->right);

    switch(current_node->operator) {
        case A_ADD:
            ssc_message(SSC_DEBUG, "[PRS] add: %d + %d\n", left_val, right_val);
            return left_val + right_val;
        case A_SUB:
            ssc_message(SSC_DEBUG, "[PRS] sub: %d - %d\n", left_val, right_val);
            return left_val - right_val;
        case A_MULT:
            ssc_message(SSC_DEBUG, "[PRS] mult: %d * %d\n", left_val, right_val);
            return left_val * right_val;
        case A_DIV:
            ssc_message(SSC_DEBUG, "[PRS] div: %d / %d\n", left_val, right_val);
            return left_val / right_val;
        case A_INTLIT:
            ssc_message(SSC_DEBUG, "[PRS] int %d\n", current_node->value);
            return current_node->value;
        default:
            ssc_message(SSC_EMERGENCY, "Encountered unknown AST node operator while trying to interpret AST tree: %d", current_node->operator);
            return 1; //This will never be reached, ssc_message will call exit(1)
    }
}