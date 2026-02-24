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
    token_tag_t type;
} token_match_t;

const token_match_t string_matches[] = {
    {"(", T_LPAREN},
    {")", T_RPAREN},
    {"[", T_LBRACKET},
    {"]", T_RBRACKET},
    {"{", T_LCBRACE},
    {"}", T_RCBRACE},
    {";", T_SEMICOLON},
    {"//", T_COMMENT},
    {"=", T_ASSIGNMENT},
    {"=>", T_EXPRESSION_START},
    {"for", T_FOR},
    {"while", T_WHILE},
    {"if", T_IF},
    {"var", T_VAR},
};

const size_t num_string_matches = sizeof(string_matches) / sizeof(token_match_t);