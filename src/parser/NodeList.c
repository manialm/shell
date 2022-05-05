#include <parser/Node.h>
#include <parser/NodeList.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

NodeList *node_list_new(void) {
    NodeList *this = malloc(sizeof(*this));
    if (this == NULL) {
        perror(__FILE__ "-> malloc failed");
        return NULL;
    }

    this->cap = 4;
    this->size = 0;
    void* maybe_ptr = malloc(sizeof(*this->data) * this->cap);
    if (maybe_ptr == NULL) {
        perror(__FILE__ "-> malloc failed");
        return NULL;
    }
    this->data = maybe_ptr;

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

        void *maybe_ptr = realloc(this->data, sizeof(*this->data) * this->cap);
        if (maybe_ptr == NULL) {
            perror(__FILE__ "-> malloc failed");
            return;
        }
        this->data = maybe_ptr;
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
