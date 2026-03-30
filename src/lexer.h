#ifndef LEXER_H
#define LEXER_H

#include "defs.h"

// Commented out these definitions for now, since we only use scan_file() in main.
/* int read_next_c();
int read_next_valid_c();
int read_token(Token *token);
int scan_intlit(int starting_c); */
void lexer_next_token();

#endif // LEXER_H