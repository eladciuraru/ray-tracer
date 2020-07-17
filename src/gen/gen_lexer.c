
typedef struct _lexer {
    cstring buff;
    u32     buff_len;

    u32 loc_index;
    // TODO: Add support for this
    u32 loc_line;
    u32 loc_col;
} lexer;


typedef enum _token_type {
    TOKEN_TYPE_EOF,
    TOKEN_TYPE_UNKOWN,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_ASSIGN,
    // TOKEN_TYPE_START_OBJECT,
    // TOKEN_TYPE_END_OBJECT,
    // TOKEN_TYPE_START_LIST,
    // TOKEN_TYPE_END_LIST,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_IDENTIFIER,
} token_type;


typedef struct _token {
    token_type type;
    cstring    buff;
    u32        buff_len;
} token;


static lexer *lexer_from_file(cstring file_path) {
    lexer *lex    = calloc(1, sizeof(*lex));
    lex->buff_len = get_file_size(file_path);
    lex->buff     = calloc(lex->buff_len, sizeof(lex->buff[0]));

    if (load_file_into(file_path, lex->buff, lex->buff_len) == false) {
        return NULL;
    }

    return lex;
}


static lexer *lexer_destroy(lexer *lex) {
    free(lex->buff);
    free(lex);

    return NULL;
}


static inline bool lexer_is_eof(lexer *lex) {
    return lex->loc_index >= lex->buff_len - 1;
}


static inline char lexer_peek(lexer *lex) {
    return (lexer_is_eof(lex)) ? EOF : lex->buff[lex->loc_index];
}


static inline char lexer_next(lexer *lex) {
    return (lexer_is_eof(lex)) ? EOF : lex->buff[++lex->loc_index];
}


static inline bool is_space(char ch) {
    switch (ch) {
        case '\n':
        case '\r':
        case '\t':
        case '\v':
        case '\f':
        case ' ':
            return true;

        default:
            return false;
    }
}


static inline bool is_num(char ch) {
    return '0' <= ch && ch <= '9';
}


static inline bool is_alpha(char ch) {
    const char UPPER_CASE_MASK = 0x20;
    char       lower           = ch | UPPER_CASE_MASK;

    return 'a' <= lower && lower <= 'z';
}


static inline bool is_alpha_num(char ch) {
    return is_alpha(ch) || is_num(ch);
}


static inline char lexer_skip_spaces(lexer *lex) {
    char ch = lexer_peek(lex);

    while (is_space(ch)) {
        ch = lexer_next(lex);
    }

    return ch;
}


static token lexer_identifier_handler(lexer *lex) {
    u32 index = lex->loc_index;

    for (char ch = lexer_peek(lex); is_alpha_num(ch) || (ch == '_'); ch = lexer_next(lex)) {
    }

    return (token) {
        .type     = TOKEN_TYPE_IDENTIFIER,
        .buff_len = lex->loc_index - index,
        .buff     = &lex->buff[index],
    };
}


static token lexer_assign_handler(lexer *lex) {
    u32 index = lex->loc_index;
    lexer_next(lex);

    return (token) {
        .type     = TOKEN_TYPE_ASSIGN,
        .buff_len = lex->loc_index - index,
        .buff     = &lex->buff[index],
    };
}


static token lexer_number_handler(lexer *lex) {
    u32 index = lex->loc_index;

    for (char ch = lexer_peek(lex); is_num(ch) || (ch == '.'); ch = lexer_next(lex)) {
    }

    return (token) {
        .type     = TOKEN_TYPE_NUMBER,
        .buff_len = lex->loc_index - index,
        .buff     = &lex->buff[index],
    };
}


static token lexer_comment_handler(lexer *lex) {
    u32 index = lex->loc_index;

    for (char ch = lexer_peek(lex); ch != '\n'; ch = lexer_next(lex)) {
    }

    return (token) {
        .type     = TOKEN_TYPE_COMMENT,
        .buff_len = lex->loc_index - index,
        .buff     = &lex->buff[index],
    };
}


static token lexer_scan_token(lexer *lex) {
    char ch = lexer_peek(lex);

    if (is_space(ch) == true) {
        ch = lexer_skip_spaces(lex);
    }

    switch (ch) {
        case EOF: return (token) { .type = TOKEN_TYPE_EOF };
        case '#': return lexer_comment_handler(lex);
        case ':': return lexer_assign_handler(lex);
        // case '{':
        // case '}':
        // case '[':
        // case ']':

        default:
            if (is_num(ch)) {
                return lexer_number_handler(lex);
            } else if (is_alpha(ch)) {
                return lexer_identifier_handler(lex);
            }
    }

    return (token) {
        .type     = TOKEN_TYPE_UNKOWN,
        .buff_len = 1,
        .buff     = &lex->buff[lex->loc_index++],
    };
}
