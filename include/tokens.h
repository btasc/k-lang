#pragma once
#include <stddef.h>

typedef enum {
    // Symbols, T for token symbol
    T_LPAREN, T_RPAREN, T_SEMICOLON, T_COMMENT, T_ASSIGNMENT, T_EXPRESSION_START,

    // T_LCBRACE = left curly brace {, T_LBRACKET = left bracket [
    T_LCBRACE, T_RCBRACE, T_LBRACKET, T_RBRACKET,

    // Keywords
    T_FOR, T_WHILE, T_IF, T_VAR,

    // Literals
    T_INT, T_STRING, T_BOOL, T_FLOAT,

    // Identifier (variables or function names)
    T_IDENTIFIER,

    // End of file
    T_EOF,

    // Used in the tree.c to show that an expression statement goes here
    T_EXPRESSION,

} token_tag_t;

typedef struct {
    const char *text;
    size_t len;
    token_tag_t tag;
} token_t;

typedef struct {
    const char *name;
    token_tag_t token;
} token_match_t;

extern token_match_t string_matches[];
extern size_t num_string_matches;