#include <stdio.h>
#include <str_array.h>

int main() {
    str_array *array = str_array_new();
    str_array_append(array, "a");
    str_array_append(array, "b");
    str_array_append(array, "c");
    str_array_append(array, "d");
    str_array_append(array, "e");
    str_array_append(array, "f");
    str_array_print(array);

    str_array_pop(array);
    str_array_pop(array);
    str_array_pop(array);
    str_array_pop(array);
    str_array_pop(array);
    str_array_pop(array);
    str_array_print(array);

    printf("\n");

    str_array_append(array, "a");
    str_array_append(array, "b");
    str_array_append(array, "c");
    str_array_append(array, "d");
    str_array_append(array, "e");
    str_array_append(array, "f");
    str_array_print(array);
}