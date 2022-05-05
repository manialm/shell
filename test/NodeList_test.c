#include <stdio.h>
#include <parser/Node.h>
#include <parser/NodeList.h>
#include <assert.h>
#include <string.h>

void check(NodeList *array, Node *data[], size_t n) {
    for (size_t i = 0; i < n; i++) {
        node_list_append(array, data[i]);
    }

    assert(array->size == n);

    for (size_t i = 0; i < n; i++) {
        assert(array->data[i]->type == data[i]->type);
        assert(array->data[i]->value == data[i]->value);
        assert(array->data[i]->child_list == data[i]->child_list);
    }
}

int main() {
    NodeList *array = node_list_new();

    Node *data[3];
    data[0] = node_new_type(REDIRECT);
    data[1] = node_new_value("ls");
    data[2] = node_new_pair(PIPE, data[0], data[1]);

    size_t n = sizeof(data) / sizeof(data[0]);
    check(array, data, n);

    assert(array->size == n);
    assert(array->data[array->size+1] == NULL);

    for (size_t i = 0; i < n; i++) {
        node_list_pop(array);
    }

    assert(array->size == 0);

    node_list_destroy(array);

    assert(array->size == 0);
    printf("Tests passed!\n");
}