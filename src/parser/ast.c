#include <parser/ast.h>
#include <parser/Node.h>
#include <parser/NodeList.h>
#include <parser/Parser.h>
#include <parser/Lexer.h>

#include <stdio.h>

int yyparse(Node **node, yyscan_t scanner);

Node *make_ast(const char *expr) {
    Node *node;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner)) {
        /* could not initialize */
        return NULL;
    }

    state = yy_scan_string(expr, scanner);

    if (yyparse(&node, scanner)) {
        /* error parsing */
        return NULL;
    }

    yy_delete_buffer(state, scanner);

    yylex_destroy(scanner);

    return node;
}