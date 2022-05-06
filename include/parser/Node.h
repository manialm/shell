#ifndef NODE_H
#define NODE_H

typedef enum Type
{
    VALUE,
    PIPE,
    COMMAND_REDIRECT,
    COMMAND,
    COMMAND_ARGS,
    REDIRECT,
    REDIRECT_IN,
    REDIRECT_OUT,
    NONE
} Type;


// forward declaration
struct NodeList;

typedef struct Node
{
    Type type;

    char *value;

    struct NodeList *child_list;
} Node;


Node *node_new_value(char *value);
Node *node_new_type(Type type);
Node *node_new_single(Type type, Node *child);
Node *node_new_pair(Type type, Node *left, Node *right);
void node_add_child(Node *this, Node *child);
void node_destroy(Node *node);

#endif /* NODE_H */