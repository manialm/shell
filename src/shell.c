#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <string.h>

#define MAXLEN 1000

void show_prompt() {
    printf("shell> ");
}

void get_comm(char comm[]) {
    fgets(comm, MAXLEN, stdin);
    comm[strcspn(comm, "\n")] = 0;
}

void exec_comm(char comm[]) {
    pid_t pid = fork();

    if (pid == 0) {
        char *argv[] = { comm, NULL };
        execvp(comm, argv);
    } else {
        wait(NULL);
    }
}

int main() {

    char comm[MAXLEN];

    while (true) {
        show_prompt();
        get_comm(comm);
        exec_comm(comm);
    }
}