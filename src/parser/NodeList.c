#include <parser/Node.h>
#include <parser/NodeList.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

NodeList *node_list_new(void) {
    NodeList *this = malloc(sizeof(*this));

    this->cap = 4;
    this->size = 0;
    this->data = malloc(sizeof(*this->data) * this->cap);

    return this;
}

void node_list_append(NodeList *this, Node *node) {
    // array is full
    if (this->size == this->cap) {
        this->cap *= 2;
        this->data = realloc(this->data, sizeof(*this->data) * this->cap);
    }

    this->data[this->size] = node;

    this->size++;
    this->data[this->size] = NULL;
}

void node_list_pop(NodeList *this) {
    if (this->size == 0) {
        return;
    }

    free(this->data[this->size - 1]);
    this->data[this->size - 1] = NULL;
    this->size--;

    if (this->size < this->cap / 2) {
        this->cap /= 2;
        this->data = realloc(this->data, sizeof(*this->data) * this->cap);
    }
}

void node_list_destroy(NodeList *this) {
    if (this == NULL) {
        return;
    }
    
    // free each node
    for (size_t i = 0; i < this->size; i++) {
        node_destroy(this->data[i]);
    }
    
    // free pointers to strings
    free(this->data);
    
    this->size = 0;
    this->cap = 4;
}