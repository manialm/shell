#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <parser/ast.h>
#include <exec.h>
#include <color.h>

#define MAXLEN 1024

void show_prompt() {
    PRINT_COLOR(BLUE, "$ ");
}

void get_command(char command[]) {
    fgets(command, MAXLEN, stdin);
    command[strcspn(command, "\n")] = 0;
}

void exec_command(char command[]) {
    execute(command);
}

int main() {

    char command[MAXLEN];

    while (true) {
        show_prompt();
        get_command(command);
        exec_command(command);
    }
}