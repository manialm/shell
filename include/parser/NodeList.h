#ifndef NODE_LIST_H
#define NODE_LIST_H

#include <stddef.h>

// forward declaration
struct Node;

// dynamic array
// reallocs when size == cap
typedef struct NodeList {
    size_t cap;
    size_t size;
    struct Node **data;
} NodeList;

NodeList *node_list_new(void);
void node_list_append(NodeList *this, Node *child);
void node_list_pop(NodeList *this);
void node_list_print(NodeList *this);
void node_list_destroy(NodeList *this);

#endif /* NODE_LIST_H */