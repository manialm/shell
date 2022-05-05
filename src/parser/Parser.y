%{

#include <parser/Node.h>
#include <parser/NodeList.h>
#include <parser/Parser.h>
#include <parser/Lexer.h>

// reference the implementation provided in Lexer.l
int yyerror(Node **expression, yyscan_t scanner, const char *msg);

%}

%code requires {
  typedef void* yyscan_t;
}

%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { Node **node }
%parse-param { yyscan_t scanner }

%union {
    char *value;
    Node *node;
}

%token TOKEN_PIPE           "|"
%token TOKEN_REDIRECT_IN    "<"
%token TOKEN_REDIRECT_OUT   ">"
%token TOKEN_AMPERSAND      "&"
%token <value> TOKEN_STRING "STRING"

%type <node> CommandRedirects
%type <node> CommandRedirect 
%type <node> Command
%type <node> CommandName
%type <node> CommandArgs
%type <node> CommandArg

%type <node> Redirects
%type <node> Redirect
%type <node> RedirectIn
%type <node> RedirectOut
%type <node> Filename

%left ">"
%left "<"
%left "|"

%%

Input
    : CommandRedirects { *node = $1; } 
    ;

CommandRedirects
    : CommandRedirect {
        $$ = node_new_type(PIPE);
        node_add_child($$, $1);
     }
    | CommandRedirects "|" CommandRedirect { node_add_child($$, $3); }
    ;

CommandRedirect
    : Command           { $$ = node_new_single(COMMAND_REDIRECT, $1); }
    | Command Redirects { $$ = node_new_pair(COMMAND_REDIRECT, $1, $2); }
    ;

Command
    : CommandName             { $$ = node_new_single(COMMAND, $1);}
    | CommandName CommandArgs { $$ = node_new_pair(COMMAND, $1, $2); }

CommandName
    : "STRING" { $$ = node_new_value($1); }
    ;

CommandArgs
    : CommandArg {
        $$ = node_new_type(COMMAND_ARGS);
        node_add_child($$, $1);
    }
    | CommandArgs CommandArg { node_add_child($$, $2); }
    ;

CommandArg
    : "STRING" { $$ = node_new_value($1); }
    ;

Redirects
    : Redirect {
        $$ = node_new_type(REDIRECT);
        node_add_child($$, $1);
    }
    | Redirects Redirect { node_add_child($$, $2); }
    ;

Redirect
    : RedirectIn        { $$ = $1; }
    | RedirectOut       { $$ = $1; }
    ;

RedirectIn
    : "<" Filename      { $$ = node_new_single(REDIRECT_IN, $2); }
    ;

RedirectOut
    : ">" Filename      { $$ = node_new_single(REDIRECT_OUT, $2); }
    ;

Filename
    : "STRING" { $$ = node_new_value($1); }

%%