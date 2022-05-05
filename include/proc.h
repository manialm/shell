#include <stddef.h>

typedef struct proc {
    char **argv;
    int stdin_fd;
    int stdout_fd;
    int close_fd;
} proc;

proc *proc_new();
void proc_execute(proc *p);
void proc_execute_bg(proc *p);
void proc_execute_multiple(proc *p[], size_t n);