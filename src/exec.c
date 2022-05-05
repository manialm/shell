#include <parser/ast.h>
#include <parser/NodeList.h>
#include <proc.h>

void execute(char input[]) {

    // Node *root = make_ast(input);
    // NodeList *child_list = root->child_list;


    int pipefd[2];
    pipe(pipefd);

    proc *p1 = proc_new();
    proc *p2 = proc_new();

    p1->argv = malloc(sizeof(char*) * 3);
    p1->argv[0] = "ls";
    p1->argv[1] = "-l";
    p1->argv[2] = NULL;

    p2->argv = malloc(sizeof(char*) * 2);
    p2->argv[0] = "lolcat";
    p2->argv[1] = NULL;

    p1->stdout_fd = pipefd[1];
    p1->close_fd = pipefd[0];
    p2->stdin_fd = pipefd[0];
    p2->close_fd = pipefd[1];
    
    proc_execute(p1);
    proc_execute(p2);
}