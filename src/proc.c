#include <proc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <parser/NodeList.h>

proc *proc_new() {
    proc *p = malloc(sizeof(*p));
    
    p->argv = NULL;

    return p;
}

proc *proc_from_node(Node *node) {
    proc *p = proc_new();

    Node *command = node->child_list->data[0];
    char *command_name = command->child_list->data[0]->value;
    
    char **argv;

    if (command->child_list->size > 1) {
        Node *command_args = command->child_list->data[1];
        size_t n_argv = command_args->child_list->size + 1;
        
        argv = malloc(sizeof(*argv) * n_argv);

        for (int i = 0; i < command_args->child_list->size; i++) {
            argv[i + 1] = command_args->child_list->data[i]->value;
        }
    } else {
        argv = malloc(sizeof(*argv) * 1);
    }

    argv[0] = command_name;
    p->argv = argv;

    return p;
}

void proc_execute(proc *p) {
    pid_t pid = fork();

    if (pid == 0) {
        execvp(p->argv[0], p->argv);
    }

    else if (pid < 0) {
        perror("fork");
    }
}

void proc_execute_first(proc *p) {
    pid_t pid = fork();

    if (pid == 0) {
        close(p->pipefd[0]);
        dup2(p->pipefd[1], STDOUT_FILENO);
        close(p->pipefd[1]);

        execvp(p->argv[0], p->argv);
    }

    else if (pid < 0) {
        perror("fork");
    }
}

void proc_execute_middle(proc *p) {
    pid_t pid = fork();

    if (pid == 0) {
        close(p->pipefd[1]);
        dup2(p->pipefd[0], STDIN_FILENO);
        close(p->pipefd[0]);

        close(p->pipefd2[0]);
        dup2(p->pipefd2[1], STDOUT_FILENO);
        close(p->pipefd2[1]);

        execvp(p->argv[0], p->argv);
    }

    else if (pid > 0) {
        close(p->pipefd[0]);
        close(p->pipefd[1]);
    }

    else {
        perror("fork");
    }
}

void proc_execute_last(proc *p) {
    pid_t pid = fork();
    
    if (pid == 0) {
        close(p->pipefd2[1]);
        dup2(p->pipefd2[0], STDIN_FILENO);
        close(p->pipefd2[0]);

        execvp(p->argv[0], p->argv);
    }
    
    else {
        close(p->pipefd2[0]);
        close(p->pipefd2[1]);
    }
}