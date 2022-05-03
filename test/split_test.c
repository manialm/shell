#include <stdio.h>
#include <str_array.h>
#include <split.h>
#include <assert.h>

int main() {
    char str[] = "hello how are you";
    str_array *res = split(str);
    str_array_print(res);
    assert(res->data[4] == NULL);   
}