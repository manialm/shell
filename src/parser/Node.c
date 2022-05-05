#include <parser/Node.h>
#include <parser/NodeList.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


static Node *node_new() {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        perror(__FILE__ "-> malloc failed");
        return NULL;
    }

    node->type = VALUE;
    node->value = 0;

    node->child_list = node_list_new();

    return node;
}

Node *node_new_value(char *value) {
    Node *node = node_new();
    assert(node != NULL);

    node->type = VALUE;
    node->value = strdup(value);

    return node;
}

Node *node_new_type(Type type) {
    Node *node = node_new();
    assert(node != NULL);

    node->type = type;

    return node;
}

Node *node_new_single(Type type, Node *child) {
    Node *node = node_new();
    assert(node != NULL);

    node->type = type;
    node_add_child(node, child);

    return node;
}

Node *node_new_pair(Type type, Node *left, Node *right) {
    Node *node = node_new();
    assert(node != NULL);

    node->type = type;
    node_add_child(node, left);
    node_add_child(node, right);

    return node;
}

Node *node_add_child(Node *this, Node *child) {
    node_list_append(this->child_list, child);
    // FIXME: what do I return?????????????????????????????????
}

void node_destroy(Node *node) {
    if (node == NULL) {
        return;
    }

    node_list_destroy(node->child_list);

    free(node->value);
    free(node);
}
