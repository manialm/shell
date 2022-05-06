#include <parser/ast.h>
#include <parser/NodeList.h>
#include <proc.h>
#include <sys/wait.h>

void execute(char input[]) {
    Node *root = make_ast(input);
    NodeList *child_list = root->child_list;
    size_t n = child_list->size;


    proc *p = proc_from_node(child_list->data[0]);

    if (n == 1) {
        proc_execute(p);
        wait(NULL);
        return;
    }

    int pipefd[2];
    pipe(pipefd);

    p->pipefd = pipefd;
    proc_execute_first(p);
    
    int pipefd2[2];

    for (int i = 1; i < n - 1; i++) {
        pipe(pipefd2);
        p = proc_from_node(child_list->data[i]);

        p->pipefd = pipefd;
        p->pipefd2 = pipefd2;
        
        proc_execute_middle(p);

        // copy old pipefd2 to pipefd for next iteration
        pipefd[0] = pipefd2[0];
        pipefd[1] = pipefd2[1];
    }

    p = proc_from_node(child_list->data[n - 1]);
    p->pipefd2 = pipefd;
    proc_execute_last(p);

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }
}