#include <stdio.h>
#include <string.h>

#include "vector.h"
#include "tokens.h"

bool is_first_identifier(const char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_other_identifier(const char c) {
    return is_first_identifier(c) || (c >= '0' && c <= '9') || c == '_';
}

vector_t make_lexer_data(const char *file_text, size_t file_text_len) {
    vector_t result = vector_make_with_capacity(sizeof(token_t), file_text_len / 4);

    const char *end = file_text + file_text_len;

    while (file_text < end) {

        // Check identifiers
        bool is_identifier = false;

        const char *start_ptr = file_text;
        char *move_ptr = (char *)file_text;

        if (is_first_identifier(*move_ptr)) {
            move_ptr += 1;

            while (is_other_identifier(*move_ptr)) {
                move_ptr += 1;
            }

            is_identifier = true;
        }

        // Now go through and check symbols
        bool is_keyword = false;
        size_t largest_n = 0;
        size_t keyword_idx = 0;

        for (size_t i = 0; i < num_string_matches; i++) {
            const size_t n = strlen(string_matches[i].name);

            if (strncmp(string_matches[i].name, file_text, n) == 0) {

                if (n > largest_n) {
                    largest_n = n;
                    keyword_idx = i;
                }

                is_keyword = true;
            }
        }

        if (!is_identifier && !is_keyword) {
            file_text += 1;

            continue;
        }
        
        token_t token;

        if (is_identifier && is_keyword) {
            // If the identifier is the same len as the keyword, we use the keyword
            if (file_text + largest_n >= move_ptr) {
                token = (token_t){file_text, largest_n, string_matches[keyword_idx].token};

                file_text += largest_n;
            } else {
                // If it's longer than the keyword, we use the identifier
                token = (token_t){file_text, move_ptr - file_text, T_IDENTIFIER};

                file_text = move_ptr;
            }

        } else if (is_identifier) {

            token = (token_t){file_text, move_ptr - file_text, T_IDENTIFIER};

            file_text = move_ptr;

        } else {

            token = (token_t){file_text, largest_n, string_matches[keyword_idx].token};
            file_text += largest_n;
        } 

        vector_push_back(&result, &token);
    }

    vector_push_back(&result, &(token_tag_t){T_EOF});

    return result;
}