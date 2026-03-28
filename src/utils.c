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