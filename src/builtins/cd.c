#include <builtins/cd.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void cd(char *name, char *argv[]) {
    if (argv[2] != NULL) {
        fprintf(stderr, "cd: too many arguments\n");
        return;
    }
    
    char *path = argv[1];

    // if no argument is provided,
    // or argument is ~, go to /home/$USER
    if (path == NULL || !strcmp(path, "~")) {
        chdir(getenv("HOME"));
    }

    else {
        chdir(path);
    }
}