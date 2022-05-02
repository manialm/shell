#ifndef STR_ARRAY_H
#define STR_ARRAY_H

#include <stddef.h>

// dynamic array
// reallocs when size == cap
typedef struct str_array {
    size_t cap;
    size_t size;
    char **data;
} str_array;

extern str_array *str_array_new(void);
extern void str_array_append(str_array *this, char *str);
extern void str_array_pop(str_array *this);
extern void str_array_print(str_array *this);
extern void str_array_destroy(str_array *this);

#endif /* STR_ARRAY_H */