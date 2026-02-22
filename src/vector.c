#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_INIT_CAPACITY 8

typedef struct {
    void* heap_ptr;
    size_t item_size;
    size_t capacity;
    size_t len;
} vector_t;

vector_t vector_make(const size_t item_size) {
    vector_t vec;

    vec.item_size = item_size;
    vec.heap_ptr = malloc(vec.item_size * VECTOR_INIT_CAPACITY);
    vec.capacity = VECTOR_INIT_CAPACITY;
    vec.len = 0;

    return vec;
}

vector_t vector_make_with_capacity(const size_t item_size, const size_t capacity) {
    vector_t vec;

    vec.item_size = item_size;
    vec.heap_ptr = malloc(vec.item_size * capacity);
    vec.capacity = capacity;
    vec.len = 0;

    return vec;
}

void vector_push_back(vector_t *v, const void* item) {
    if (v == nullptr) {
        fprintf(stderr, "Warning: Attempted to push item to nullptr in vector_push_back");
        return;
    }

    if (v->capacity <= v->len) {
        v->capacity = v->capacity == 0 ? VECTOR_INIT_CAPACITY : v->capacity * 2;

        void* realloc_res = realloc(v->heap_ptr, v->item_size * v->capacity);

        // If it is updated to where this does not crash the program with exit,
        // remember to update capacity only if realloc isn't a failure
        if (realloc_res == nullptr) {
            free(v->heap_ptr);

            fprintf(stderr, "Fatal Error: Out of memory at vector_push_back during realloc");
            exit(EXIT_FAILURE);
        }

        v->heap_ptr = realloc_res;
    }

    void* end = (char*)v->heap_ptr + (v->len * v->item_size);
    memcpy(end, item, v->item_size);

    v->len++;
}

void vector_free(vector_t *v) {
    if (v != nullptr) return;

    if (v->heap_ptr != nullptr) {
        free(v->heap_ptr);
    }

    v->heap_ptr = nullptr;
    v->capacity = 0;
    v->len = 0;
}