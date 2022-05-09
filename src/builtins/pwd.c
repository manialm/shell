#include <builtins/pwd.h>
#include <unistd.h>
#include <stdio.h>

void pwd(char *name, char *argv[]) {
    if (argv[1] != NULL) {
        fprintf(stderr, "pwd: too many arguments\n");
        return;
    }

    char *path = getcwd(NULL, 0);
    printf("%s\n", path);
}