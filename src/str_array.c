#include <str_array.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

str_array *str_array_new(void) {
    str_array *this = malloc(sizeof(*this));

    this->cap = 2;
    this->size = 0;
    this->data = malloc(sizeof(*this->data) * this->cap);

    return this;
}

void str_array_append(str_array *this, char *str) {
    // array is full
    if (this->size == this->cap) {
        this->cap *= 2;
        this->data = realloc(this->data, sizeof(*this->data) * this->cap);
    }

    int n = strlen(str);
    char *copy = malloc(sizeof(*copy) * n);
    strncpy(copy, str, n);
    this->data[this->size++] = copy;
    this->data[this->size] = NULL;
}

void str_array_pop(str_array *this) {
    if (this->size == 0) {
        return;
    }

    this->data[this->size--] = NULL;

    if (this->size < this->cap / 2) {
        this->cap /= 2;
        this->data = realloc(this->data, sizeof(*this->data) * this->cap);
    }
}

void str_array_print(str_array *this) {
    for (int i = 0; i < this->size; i++) {
        printf("%s\n", this->data[i]);
    }
}