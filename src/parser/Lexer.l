%{

/*
 * Lexer.l file
 * To generate the lexical analyzer run: "flex Lexer.l"
 */

#include <parser/Node.h>
#include <parser/Parser.h>

#include <stdio.h>
#include <string.h>

%}

%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

%%

[ \r\n\t]*   { continue; /* Skip blanks. */ }
[a-zA-Z0-9\-\.\/]+       { yylval->value = strdup(yytext); return TOKEN_STRING; }

"|"          { return TOKEN_PIPE; }
"<"          { return TOKEN_REDIRECT_IN; }
">"          { return TOKEN_REDIRECT_OUT; }
"&"          { return TOKEN_AMPERSAND; }

.            { continue; /* Ignore unexpected characters. */}

%%

int yyerror(Node **node, yyscan_t scanner, const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    return 0;
}