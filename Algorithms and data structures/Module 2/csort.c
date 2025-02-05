#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct word {
    char *p;
    int len;
} word;

static int get_words(char *s, word *a) {
    char prev = ' ';
    int num_words = 0;
    while (*s != '\0') {
        if (isspace(prev) && !isspace(*s)) {
            char *start = s;
            while (*s != '\0' && !isspace(*s)) *s++;
            int l = (int)(s - start);
            a->p = start;
            a->len = l;
            num_words++;
            a++;
        } else s++;
    }
    return num_words;
} // не только узнали количество слов, но и для каждого слова
  // запомнили его длину и само слово

void csort(char *src, char *dest) {
    word *words = calloc(1001, sizeof(word));
    int num_of_words = get_words(src, words);
    words = realloc(words, num_of_words * sizeof(word));
    int *len_word_count = calloc(num_of_words, sizeof(int));

    for (int i = 0; i < num_of_words - 1; i++) {
        for (int j = i + 1; j < num_of_words; j++) {
            if (words[j].len < words[i].len) {
                len_word_count[i]++;
            } else len_word_count[j]++;
        }
    }
// для случая qqq  www  t  aa rrr  bb  x y zz
// len_word_count = [6, 7, 0, 3, 8, 4, 1, 2, 5]

    int id = 0;
    for (int i = 0; i < num_of_words; i++) {
        int j = 0;
        while (len_word_count[j] != i) j++; // ищем следующее слово
        char *word1 = words[j].p;
        for (int i = 0; i < words[j].len; i++) {
            dest[id] = *word1;
            id++;
            word1++; // увеличили адрес на 1, т.е. сместились к следующей букве слова
        }
        if (num_of_words - i > 1) {
            dest[id] = ' ';
            id++;
        } //поочерёдно записали символы слова и поставили пробел
    }
    dest[id] = '\0';
    free(words);
    free(len_word_count);
}

int main(int argc, char **argv) {
    char *a = calloc(1000, sizeof(char));
    char *res = calloc(1000, sizeof(char));
    fgets(a, 1000, stdin);
    csort(a, res);
    printf("%s", res);
    free(a);
    free(res);
    return 0;
}