#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

char* open_null_terminated_file(const char *path);

int main(int argc, char *argv[]) {
    if (argc <= 0) {
        fprintf(stderr, "Fatal Error: No file specified");
        exit(EXIT_FAILURE);
    }

    char *file_text = open_null_terminated_file(argv[1]);



    return 0;
}

char* open_null_terminated_file(const char *path) {
    // Request file
    FILE *file = fopen(path, "r");

    // Check if file opened
    if (file == nullptr) {
        fprintf(stderr, "Fatal Error: Could not open file %s\n", path);
        exit(EXIT_FAILURE);
    }

    // Go to end of file
    fseek(file, 0, SEEK_END);

    // Get size from the end of file
    size_t size = ftell(file);

    // Go back to beginning
    rewind(file);

    if (size == 0) {
        fprintf(stderr, "Fatal Error: Empty file %s\n", path);
    }

    char *buffer = malloc(size + 1);

    if (buffer == nullptr) {
        fprintf(stderr, "Fatal Error: Could not allocate memory for file buffer");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // 1 is the size of elements in the file, in this case chars
    // result is now equal to the number of elements read, so num of chars
    size_t result = fread(buffer, 1, size, file);

    // Close file aftr
    fclose(file);

    // Add the null terminator for the end of file token
    // Note that result is the num of elements, so we dont need to add one to get to the last character
    buffer[result] = '\0';

    return buffer;
}