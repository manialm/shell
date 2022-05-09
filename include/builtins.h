#include <stdbool.h>

extern char *builtins[];

typedef void (*builtin_func_t)(char *name, char *argv[]);

bool builtin_find(char *name);

void builtin_execute(char *name, char *argv[]);