#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"
#include "format.h"
#include "vector.h"
#include "tokens.h"

/*
    I want this to be a tree where I use an arena to store user variables

    The idea is that I want all things to boil down to an expression, something that
    takes some ptrs to the arena variables and some literals that can be evaluated

    The arena should store these expressions as almost functions 

    I think this is what an interpreter does, and it is the easiest way to do it thats
    not taking a cheaper route like a transpiler but not as hard as bytecode or llvm

    For now I don't have to worry about the interpreter, this is just for the tree
    to make the expressions 
*/

typedef struct {

} tree_t;

vector_t tree_parse_tokens(const vector_t *tokens, const char *str_start, const char *str_end) {
    token_t *tok_ptr = tokens->heap_ptr;

    /*while (tok_ptr++) {

        // Check statement matches

    }*/
}

// An expression is something that has an evaluation of
// some combinations of literals and variables
typedef struct {
    size_t len;
    token_t *tokens;
} expression_t;

typedef struct {
    bool was_successful;

    union {
        char* error;
        expression_t exp;
    } result;

} get_expression_res_t;

expression_t make_expression(token_t *tokens, const char *str_start, const char *str_end) {
    expression_t res;

    if(tokens->tag != T_EXPRESSION_START && tokens->tag != T_LCBRACE) {
        fprintf(stderr, "Unreachable: Expression starts with non expression token");
        exit(EXIT_FAILURE);
    }

    if (tokens->tag == T_EXPRESSION_START) {

        const token_t *move_ptr = tokens;

        while (move_ptr->tag != T_SEMICOLON && move_ptr->tag != T_EOF) {
            move_ptr += 1;
        }

        if(move_ptr->tag == T_EOF) {
            fprintf(stderr, "Fatal Error: End of file reached during expression parse");
            exit(EXIT_FAILURE);
        }

        if(move_ptr->tag == T_SEMICOLON) {
            res = (expression_t){(size_t)(move_ptr - tokens), tokens};

            return res;
        }

        // If it doesn't match to a semicolon or EOF, then it should segfault or stall
        // Its not ideal but I'm not sure how to stop it without adding logic to the move_ptr++
    }
}

// A statement is a for loop, if statement, or a variable
// Its any combination of tokens that uses an expression in some way
// For example, a variable evaluates an expression and assigns it, so its an expression
typedef enum {
    S_FOR, S_WHILE, S_IF, S_DEFINE_FUNCTION, S_RUN_FUNCTION, S_VAR, S_ASSIGNMENT,
} statement_tag_t;

typedef struct {
     statement_tag_t tag;
     expression_t exp;
} statement_t;

typedef struct {
    statement_tag_t statement;
    size_t len;
    token_tag_t *tokens;
} statement_match_t;

// This uses odd syntax of (type[]){v1, v2
const statement_match_t statement_matches[] = {
    {S_FOR, 8, (token_tag_t[]){T_FOR, T_LPAREN, T_VAR, T_IDENTIFIER, T_EXPRESSION, T_EXPRESSION, T_EXPRESSION, T_RPAREN}},
    {S_WHILE, 2, (token_tag_t[]){T_WHILE, T_EXPRESSION}},
    {S_IF, 2, (token_tag_t[]){T_IF, T_EXPRESSION}},
    {S_DEFINE_FUNCTION, 4, (token_tag_t[]){T_IDENTIFIER, T_LPAREN, T_RPAREN, T_EXPRESSION}},
    {S_RUN_FUNCTION, 3, (token_tag_t[]){T_IDENTIFIER, T_LPAREN, T_RPAREN}},
    {S_VAR, 3, (token_tag_t[]){T_VAR, T_IDENTIFIER, T_EXPRESSION}},
    {S_ASSIGNMENT, 3, (token_tag_t[]){T_IDENTIFIER, T_ASSIGNMENT, T_EXPRESSION}}
};