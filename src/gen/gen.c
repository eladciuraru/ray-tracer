#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>

#include "renderer\renderer.h"
#include "gen\gen_file.c"
#include "gen\gen_lexer.c"


static void print_token(token tok) {
    printf("[*] Token - type: %d, value.size: %d, value.data: %.*s\n",
           tok.type, tok.buff_len, tok.buff_len, tok.buff);
}


int main(int argc, char *argv[]) {
    cstring file_path = "src\\gen\\example.txt";

    lexer *lex = lexer_from_file(file_path);
    if (lex == NULL) {
        fprintf(stderr, "[!] Failed to load file %s", file_path);
        return EXIT_FAILURE;
    }

    token tok = lexer_scan_token(lex);
    while (tok.type != TOKEN_TYPE_EOF) {
        print_token(tok);

        tok = lexer_scan_token(lex);
    }
    lex = lexer_destroy(lex);

    return EXIT_SUCCESS;
}
