#include <str_array.h>
#include <string.h>

str_array *split(char str[]) {
    const int MAXLEN = 1024;
    char word[MAXLEN];

    str_array *res = str_array_new();
    size_t word_i = 0;

    for (int i = 0; str[i]; i++) {
        switch (str[i]) {
            case ' ':
                word[word_i] = 0;
                str_array_append(res, word);
                word_i = 0;
                break;
            
            default:
                word[word_i++] = str[i];
                break;
        }
    }

    word[word_i] = 0;
    str_array_append(res, word);

    return res;
}