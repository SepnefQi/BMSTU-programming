#include <stdio.h>
#include <stdlib.h>

struct Elem {
    struct Elem *prev, *next;
    int v;
};

void sort(struct Elem *head, struct Elem *newe) {
    struct Elem *curr = head->next;
    while (curr != head && curr->v < newe->v) curr = curr->next;

    newe->next = curr;
    newe->prev = curr->prev;
    curr->prev->next = newe;
    curr->prev = newe;
}


void listisort(struct Elem *head) {
    if (head == NULL || head->next == head) return;
    struct Elem *sh = malloc(sizeof(struct Elem));
    sh->prev = sh;
    sh->next = sh;

    struct Elem *curr = head->next;
    while(curr != head) {
       struct Elem *next = curr->next;
       curr->next = NULL;
       curr->prev = NULL;
        sort(sh, curr);
        curr = next;
    }

    curr = sh->next;
    struct Elem *prev = head;
    while(curr != sh) {

        prev->next = curr;
        curr->prev = prev;
        prev = curr;
        curr = curr->next;
    }
    prev->next = head;
    head->prev = prev;

    free(sh);
}

int main() {
    int n, val;
    scanf("%d", &n);

    if (n <= 0) return 0;

    struct Elem *head = malloc(sizeof(struct Elem));
    if (head == NULL) return 1;
    head->next = head;
    head->prev = head;


    struct Elem *last = head;
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        struct Elem *newe = malloc(sizeof(struct Elem));
        if (newe == NULL) return 1;
        newe->v = val;
        newe->next = head;
        newe->prev = last;
        last->next = newe;
        head->prev = newe;
        last = newe;
    }

    listisort(head);

    struct Elem *curr = head->next;
    while(curr != head) {
        printf("%d ", curr->v);
        curr = curr->next;
    }

    curr = head->next;
    while (curr != head) {
        struct Elem *now = curr;
        curr = curr->next;
        free(now);
    }
    free(head);

    return 0;
}