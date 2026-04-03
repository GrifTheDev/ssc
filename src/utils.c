#include "defs.h"
#include "data.h"

// Takes in a char (cast to int) and returns 1 if it is a digit and 0 if it is not.
int is_digit(int digit) {
    return digit >= 48 && digit <= 57;
}

// Similar to strchr, but returns the index at which the needle was found instead of a pointer to it.
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

// Prints out a neatly formatted message to stdout, quits the program with exit code one on any level lower than
// or equal to 3. Supports variatic input of printf-like arguments.
void ssc_message(SSC_LogLevel level, char *fmessage, ...) {
    #ifndef DEV
        if (level == SSC_DEBUG) return;
    #endif //Dev

    char *debug_message_prefix[] = { 
        "EMERGENCY", 
        "ALERT", 
        "CRITICAL", 
        "ERROR", 
        "WARNING", 
        "NOTICE", 
        "INFO", 
        "DEBUG" 
    };

    va_list args;
    va_start(args, fmessage);
    printf("[%s] ", debug_message_prefix[level]);
    vprintf(fmessage, args);
    va_end(args);

    if (level <= 3) exit(1);
}