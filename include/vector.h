#pragma once
#include <stddef.h>

typedef struct {
    void* heap_ptr;
    size_t item_size;
    size_t capacity;
    size_t len;
} vector_t;

vector_t vector_make(size_t item_size);
vector_t vector_make_with_capacity(size_t item_size, size_t capacity);

void vector_push_back(vector_t *v, const void* item);
void vector_free(vector_t *v);
void* vector_at(vector_t *v, size_t idx);