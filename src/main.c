#include "defs.h"
#include "utils.h"
#include "lexer.h"

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
        printf("[ERR] No input provided\n\n");
        printf("[ERR] Usage: ssc main\n");
        return 1;
    }
    init();
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
