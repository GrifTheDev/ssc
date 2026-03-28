#include "defs.h"
#include "data.h"
#include "utils.h"

static void putback_c(int character) {
    putback = character;
}

static int read_next_c() {
    int character;
    
    if (putback) {
        character = putback;
        putback = 0;
        return character;
    }
    
    character = fgetc(input_file); // fgetc moves the character pointer, thus consuming the char
    if (character == '\n') {
        line_number++;
        col_number = 1;
    } else  if (character != EOF) {
        col_number += 1;
    }
    return character;
}

static int read_next_valid_c() {
    int character;

    character = read_next_c();
    while (character == ' ' || character == '\t' || character == '\n' || character == '\r' || character == '\f') {
        character = read_next_c();
    }
    return character;
}

// Takes in a char (cast to int, assumed to adhere to is_digit(c) == 1) and returns it as an integer.
static int scan_intlit(int character) {
    int current, value = 0;

    while ((current = chr_pos("0123456789", character)) >= 0) {
        value *= 10;
        value += current;
        character = read_next_valid_c();
    }

    putback_c(character);
    return value;
}

static int read_token(Token *token) {

    int character = read_next_valid_c();

    switch (character)
    {
    case '+':
        token->token_type = T_ADD;
        break;
    case '-':
        token->token_type = T_SUB;
        break;
    case '*':
        token->token_type = T_MULT;
        break;
    case '/':
        token->token_type = T_DIV;
        break;
    case EOF:
        return 0;
    default:
        if (is_digit(character)) {
            token->token_type = T_INTLIT;
            token->value = scan_intlit(character);
        } else {
            printf("Error on line %d, invalid token", line_number);
        }

        break;
    }

    return 1;
}

void scan_file() {
    Token current_tok;

    char *tok_lookup[] = { "+", "-", "*", "/", "intlit"};

    while(read_token(&current_tok)) {
        if (current_tok.token_type == T_INTLIT) {
            printf("[TOK_DETECT] [%d:%d] Type: %s Value: %d\n", line_number, col_number, tok_lookup[current_tok.token_type], current_tok.value);
        } else {
            printf("[TOK_DETECT] [%d:%d] Type: %s Value: %c\n", line_number, col_number, tok_lookup[current_tok.token_type], current_tok.value);
        }
    }
}