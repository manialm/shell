#include <proc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

proc *proc_new() {
    proc *p = malloc(sizeof(*p));
    if (p == NULL){
        perror(__FILE__ "-> malloc failed");
        return NULL;
    }

    p->stdin_fd = STDIN_FILENO;
    p->stdout_fd = STDOUT_FILENO;
    p->argv = NULL;
    p->close_fd = -1;

    return p;
}

void proc_execute(proc *p) {
    int status;

    pid_t pid = fork();

    if (pid == 0) {
        close(p->close_fd);
        dup2(p->stdout_fd, STDOUT_FILENO);
        dup2(p->stdin_fd, STDIN_FILENO);
        execvp(p->argv[0], p->argv);
    } else if (pid > 0) {
        printf("%s %d\n", p->argv[0], p->close_fd);
        wait(&status);
        printf("here is fd: %d\n", p->close_fd);
        close(4);

        if (WIFEXITED(status)) {
            printf("%s exited.\n", p->argv[0]);
        } else {
            printf("%d\n", status);
        }
    } else {
        perror("fork");
    }
}

void proc_execute_bg(proc *p) {
    int status;

    pid_t pid = fork();

    if (pid == 0) {
        dup2(p->stdout_fd, STDOUT_FILENO);
        dup2(p->stdin_fd, STDIN_FILENO);
        execvp(p->argv[0], p->argv);
    } else if (pid > 0) {
        waitpid(pid, &status, WNOHANG);

        // if ...  
    } else {
        perror("fork");
    }
}
