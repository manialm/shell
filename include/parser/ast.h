#ifndef AST_H
#define AST_H

#include <parser/Node.h>
#include <parser/Parser.h>
#include <parser/Lexer.h>

int yyparse(Node **node, yyscan_t scanner);

Node *make_ast(const char *expr);

#endif /* AST_H */