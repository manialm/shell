#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <parser/ast.h>
#include <parser/NodeList.h>
#include <proc.h>

void execute(char input[]) {

    // Node *root = make_ast(input);
    // NodeList *child_list = root->child_list;


    int pipefd[2];
    int ret = pipe(pipefd);
    if (ret != 0) {
        perror(__FILE__"-> pipe failed");
        return;
    }

    proc *p1 = proc_new();
    proc *p2 = proc_new();
    if(p1 == NULL || p2 == NULL) {
        perror(__FILE__"-> proc_new failed");
        return;
    }

    void* maybe_ptr = malloc(sizeof(char*) * 3);
    if (maybe_ptr == NULL) {
        perror(__FILE__ "-> malloc failed");
        return;
    }
    p1->argv = maybe_ptr;
    p1->argv[0] = "ls";
    p1->argv[1] = "-l";
    p1->argv[2] = NULL;

    maybe_ptr = malloc(sizeof(char*) * 2);
    if (maybe_ptr == NULL) {
        perror(__FILE__ "-> malloc failed");
        return;
    }
    p2->argv = maybe_ptr;
    p2->argv[0] = "lolcat";
    p2->argv[1] = NULL;

    p1->stdout_fd = pipefd[1];
    p1->close_fd = pipefd[0];
    p2->stdin_fd = pipefd[0];
    p2->close_fd = pipefd[1];
    
    proc_execute(p1);
    proc_execute(p2);
}
