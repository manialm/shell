#include <shell_execvp.h>
#include <unistd.h>
#include <builtins.h>

void shell_execvp(char *name, char *argv[]) {
    if (builtin_find(name)) {
        builtin_execute(name, argv);
    }

    else {
        execvp(name, argv);
    }
}