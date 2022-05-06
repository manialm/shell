#include <stddef.h>
#include <parser/Node.h>

typedef struct proc {
    char **argv;

    // pointer to array of 2
    int *pipefd;
    int *pipefd2;
} proc;

proc *proc_new();
void proc_from_node(proc *p, Node *node);
void proc_execute(proc *p);
void proc_execute_first(proc *p);
void proc_execute_middle(proc *p);
void proc_execute_last(proc *p);
void proc_destroy(proc *p);