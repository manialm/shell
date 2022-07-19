#include <proc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <parser/NodeList.h>
#include <shell_execvp.h>

proc *proc_new() {
    proc *p = malloc(sizeof(*p));
    
    p->argv = NULL;

    return p;
}

void proc_from_node(proc *p, Node *node) {

    Node *command = node->child_list->data[0];
    char *command_name = command->child_list->data[0]->value;
    
    char **argv;

    size_t n_argv;

    if (command->child_list->size > 1) {
        Node *command_args = command->child_list->data[1];

        // + 2: 1 for command_name and 1 for NULL
        n_argv = command_args->child_list->size + 2;
        
        argv = malloc(sizeof(*argv) * n_argv);

        for (int i = 0; i < command_args->child_list->size; i++) {
            argv[i + 1] = command_args->child_list->data[i]->value;
        }
    } else {
        n_argv = 2;
        argv = malloc(sizeof(*argv) * n_argv);
    }

    argv[0] = command_name;
    argv[n_argv - 1] = NULL;
    p->argv = argv;
}

void proc_execute(proc *p) {
    pid_t pid = fork();

    if (pid == 0) {
        shell_execvp(p->argv[0], p->argv);
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

        shell_execvp(p->argv[0], p->argv);
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

        shell_execvp(p->argv[0], p->argv);
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

        shell_execvp(p->argv[0], p->argv);
    }
    
    else {
        close(p->pipefd2[0]);
        close(p->pipefd2[1]);
    }
}

void proc_destroy(proc *p) {
    if (p->argv)
        free(p->argv);

    if (p)
        free(p);
}