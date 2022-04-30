#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <string.h>

#include <str_array.h>
#include <split.h>
#include <color.h>

const int MAXLEN = 1024;

void show_prompt() {
    PRINT_COLOR(BLUE, "$ ");
}

void get_comm(char comm[]) {
    fgets(comm, MAXLEN, stdin);
    comm[strcspn(comm, "\n")] = 0;
}

void exec_comm(char comm[]) {
    pid_t pid = fork();

    if (pid == 0) {
        str_array *arr = split(comm);
        char **argv = arr->data;
        execvp(argv[0], argv);
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