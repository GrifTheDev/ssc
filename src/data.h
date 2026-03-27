/*
    This cool trick allows us to define global variables once and then use the extern keyword
    to let the linker know that the variable definitions are located elsewhere. In our case,
    the definitions are going to be located in main.c where we will define extern_ so that 
    our variables get assigned, but everywhere else we import this header file the variables
    will resolve to be extern.
*/
#ifndef extern_
#define extern_ extern
#endif // extern_

extern_ int line_number = 1;
extern_ int col_number = 1;
extern_ int putback = 0;
extern_ FILE *input_file;