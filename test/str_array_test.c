#include <stdio.h>
#include <str_array.h>
#include <assert.h>
#include <string.h>

void check(str_array *array, char *data[], size_t n) {
    for (size_t i = 0; i < n; i++) {
        str_array_append(array, data[i]);
    }

    assert(array->size == n);

    for (size_t i = 0; i < n; i++) {
        size_t n = strlen(data[i]);
        assert(strncmp(array->data[i], data[i], n) == 0);
    }
}

int main() {
    str_array *array = str_array_new();
    char *data[] = {"ab", "cd", "ef"};
    size_t n = sizeof(data) / sizeof(data[0]);
    check(array, data, n);

    str_array_print(array);

    assert(array->size == n);
    assert(array->data[array->size+1] == NULL);

    for (size_t i = 0; i < n; i++) {
        str_array_pop(array);
    }

    str_array_print(array);

    assert(array->size == 0);

    str_array_destroy(array);

    str_array_print(array);
    assert(array->size == 0);

    printf("Tests passed!\n");
}