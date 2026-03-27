#include <stdio.h>

#define extern_
#include "data.h"
#undef extern_

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

int read_next_c();
int read_next_valid_c();
int read_token(Token *token);
int is_digit(int digit);
int chr_pos(char *haystack, char needle);
int scan_intlit(int starting_c);
void scan_file();

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("[ERR] No input provided\n\n");
        printf("[ERR] Usage: ssc main\n");
        return 1;
    }

    input_file = fopen(argv[1], "r");

    printf("Scanning %s\n", argv[1]);
    scan_file();
    
   /*  printf("|read valid = %c read next = %c|\n", read_next_valid_c(), read_next_c() );
    printf("|read valid = %c read next = %c|\n", read_next_valid_c(), read_next_c() ); // printf validates functions from right to left???
    printf("|read valid = %c read next = %c|\n", read_next_valid_c(), read_next_c() );
    printf("|read valid = %c read next = %c|\n", read_next_valid_c(), read_next_c() );
    
    printf("|line number = %d|\n", line_number); */
    return 0;

}

static void putback_c(int character) {
    putback = character;
}

int read_next_c() {
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

int read_next_valid_c() {
    int character;

    character = read_next_c();
    while (character == ' ' || character == '\t' || character == '\n' || character == '\r' || character == '\f') {
        character = read_next_c();
    }
    return character;
}

int is_digit(int digit) {
    return digit >= 48 && digit <= 57;
}

// kind of like strchr, but instead of returning a pointer to the first occurence of the needle, it returns the index at which is is found
int chr_pos(char *haystack, char needle) {
    int index = 0;
    while (*haystack) {
        if (*haystack == needle) {
            return index;
            break;
        }
        index++;
        haystack++;
    }
    return -1;
}

int scan_intlit(int character) {
    int current, value = 0;

    while ((current = chr_pos("0123456789", character)) >= 0) {
        value *= 10;
        value += current;
        character = read_next_valid_c();
    }

    putback_c(character);
    return value;
}

int read_token(Token *token) {

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