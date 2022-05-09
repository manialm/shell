#include <builtins.h>
#include <builtins/cd.h>
#include <builtins/pwd.h>
#include <stddef.h>
#include <string.h>

char *builtins[] = {
    "cd",
    "pwd"
};

bool builtin_find(char *name) {
    size_t len = sizeof(builtins) / sizeof(builtins[0]);
    for (int i = 0; i < len; i++) {
        if (!strcmp(builtins[i], name)) {
            return true;
        }
    }

    return false;
}

void builtin_execute(char *name, char *argv[]) {
    builtin_func_t builtin;

    if (!strcmp(name, "cd")) {
        builtin = cd;
    }
    
    else if (!strcmp(name, "pwd")) {
        builtin = pwd;
    }

    builtin(name, argv);
}