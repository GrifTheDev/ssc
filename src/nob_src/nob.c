#define NOB_IMPLEMENTATION
#include "nob.h"

#define BUILD_FOLDER "./"
#define SOURCE_FOLDER "./"
#define DEV

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    if(!nob_mkdir_if_not_exists(BUILD_FOLDER)) return 1;

    Nob_Cmd cmd = {0};

    nob_cmd_append(&cmd, "cc", SOURCE_FOLDER"main.c", SOURCE_FOLDER"utils.c", SOURCE_FOLDER"lexer.c", SOURCE_FOLDER"parser.c");
    nob_cmd_append(&cmd, "-o", BUILD_FOLDER"ssc");
    nob_cmd_append(&cmd, "-Wextra", "-Wall");

    #ifdef DEV
        nob_cmd_append(&cmd, "-ggdb");
    #endif // DEV

    if (!nob_cmd_run(&cmd)) return 1;
}