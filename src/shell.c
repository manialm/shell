#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <string.h>

#include <parser/ast.h>
#include <exec.h>
#include <color.h>

const int MAXLEN = 1024;

void show_prompt() {
    PRINT_COLOR(BLUE, "$ ");
}

void get_comm(char comm[]) {
    int first = getc(stdin);

    if (first == EOF)
        exit(0);

    comm[0] = first;
    fgets(comm + 1, MAXLEN - 1, stdin);

    comm[strcspn(comm, "\n")] = 0;
}

void exec_comm(char comm[]) {
    execute(comm);
}

int main() {

    char comm[MAXLEN];

    while (true) {
        show_prompt();
        get_comm(comm);
        exec_comm(comm);
    }
}
