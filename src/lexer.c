#include "vector.h"

typedef enum {
    LPAREN,
    RPAREN,
    OPERATOR,
    NUMBER,
    IDENTIFIER,
    EOF,
} token_tag_t;

typedef struct {
    const char *text;
    token_tag_t tag;
    size_t len;
} token_t;

typedef struct {
    vector_t tokens;
} lexer_data_t;

lexer_data_t make_lexer_data(char *file_text, size_t file_text_len) {
    lexer_data_t data;

    return data;
}