#include <sh_execvp.h>
#include <unistd.h>
#include <builtins.h>

void sh_execvp(char *name, char *argv[]) {
    if (builtin_find(name)) {
        builtin_execute(name, argv);
    }

    else {
        execvp(name, argv);
    }
}