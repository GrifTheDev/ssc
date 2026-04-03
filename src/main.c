#include "defs.h"
#include "utils.h"
#include "lexer.h"
#include "parser.h"

#define extern_
#include "data.h"
#undef extern_

void init() {
    line_number = 1;
    col_number = 1;
    putback = 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        ssc_message(SSC_ERROR, "No input file provided\n\nUsage ssc ./main.c\n", "");
        return 1;
    }
    init();
    input_file = fopen(argv[1], "r");

    printf("Scanning %s\n", argv[1]);
    lexer_next_token();
    AST_node *ast = parser_bin_exp(0);
    int final_res = interpret_AST(ast);
    printf("final result of ast interpretation for %s: %d\n", argv[1], final_res);
    

    
   /*  printf("|read valid = %c read next = %c|\n", read_next_valid_c(), read_next_c() );
    printf("|read valid = %c read next = %c|\n", read_next_valid_c(), read_next_c() ); // printf validates functions from right to left???
    printf("|read valid = %c read next = %c|\n", read_next_valid_c(), read_next_c() );
    printf("|read valid = %c read next = %c|\n", read_next_valid_c(), read_next_c() );
    
    printf("|line number = %d|\n", line_number); */
    return 0;

}
