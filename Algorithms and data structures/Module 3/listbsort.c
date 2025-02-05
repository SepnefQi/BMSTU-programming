#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
    char *word;
    int l;
}typedef word;

struct Elem {
    struct Elem *next;
    char *word;
};

struct Elem *InitElem(char *w, struct Elem *prev){
    struct Elem *new = malloc(sizeof(struct Elem));
    new->word = w;
    new->next = NULL;
    if(prev == NULL) return new;
    prev->next = new;
    return new;
}

int nextWord(char *s, word *w){
    int k=0;
    while (s[w->l] == ' ' && s[w->l] != '\0' && s[w->l] != '\n') w->l++;
    if(s[w->l] == '\0' || s[w->l] == '\n') return 0;
    w->word = calloc(1000, sizeof(char));
    while (s[w->l] != ' ' && s[w->l] != '\0' && s[w->l] != '\n'){
        w->word[k++] = s[w->l++];
    }
    return 1;
}

struct Elem *InitList(char* s){
    struct Elem *nl = NULL;
    word *w = malloc(sizeof(word));
    w->l = 0;
    struct Elem *prev = NULL;
    while (nextWord(s, w)) {
        if (nl == NULL){ //Сработает лишь 1 раз
            nl = InitElem(w->word, NULL);
            prev = nl;
        } else{
            prev = InitElem(w->word, prev);
        }
    }
    free(w);
    return nl;
}

struct Elem *bsort(struct Elem *list) {
    if (!list || !list->next) return list;

    int swapped;
    struct Elem *ptr1;
    struct Elem *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = list;

        while (ptr1->next != lptr) {
            if (strlen(ptr1->word) > strlen(ptr1->next->word)) {
                char *swap = ptr1->word;
                ptr1->word = ptr1->next->word;
                ptr1->next->word = swap;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return list;
}

int main() {
    char s[1000];
    fgets (s, 1000, stdin);
    struct Elem *list = InitList(s);
        
    list = bsort(list);
        
    while (list) {
        printf("%s ", list->word);
        struct Elem *next = list->next;
        free(list->word);
        free(list);
        list = next;
    }
    return 0;
}