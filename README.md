I wanted to get into compilers, so I did. I'm going to be following along to write a compiler for a subset of the C programming language. The guide I am following is https://github.com/DoctorWkt/acwj.

This project uses the [nob.h](https://github.com/tsoding/nob.h) build system.
Cool gist about using submodules in git: https://gist.github.com/gitaarik/8735255.

# Notes
`30/03/2026` I've decided to change up (as opposed to acwj) my appraoch to handling tokens. Instead of calling `lexer_next_token()` first in main then in some static functions in parser.c, I've decided to keep the `lexer_next_token()` function call exclusively in `parser_bin_exp()`. At this stage of development the lexer shouldn't have to be called exclusively, and it's cleaner than to track a million instances of calling the scan function.
