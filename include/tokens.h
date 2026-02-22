#pragma once
#include <stddef.h>

typedef enum {
    // Symbols, T_S for token symbol
    T_S_LPAREN, T_S_RPAREN, T_S_SEMICOLON, T_S_EOF, T_S_COMMENT,

    // Keywords, T_K for token keyword
    T_K_FOR, T_K_WHILE, T_K_IF,

    // Literals, T_L for token literal
    T_L_INT, T_L_FLOAT, T_R_BOOL, T_R_FLOAT,

    // Identifier (variables or function names)
    T_IDENTIFIER,

} token_tag_t;

typedef struct {
    const char *text;
    token_tag_t tag;
    size_t len;
} token_t;

typedef struct {
    const char *name;
    token_tag_t type;
} token_string_t;

const token_string_t keywords[];

const token_string_t symbols[];