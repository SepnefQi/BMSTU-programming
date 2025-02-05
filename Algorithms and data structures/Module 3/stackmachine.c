#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack{
    long val;
    struct stack *prev;
};

struct stack *newStack(long val, struct stack *prev){
    struct stack *new = malloc(sizeof(struct stack));
    new->prev = prev;
    new->val = val;
    return new;
}

int main() {
    struct stack *s = NULL;
    char command[10];
    long x;
    scanf("%s", command);
    while (strcmp(command, "END") < 0 || strcmp(command, "END") > 0) {
        if (strcmp(command, "CONST") == 0) {
            scanf("%ld", &x);
            s = newStack(x, s);
        }
        else if (strcmp(command, "ADD") == 0) {
            struct stack *first = s;
            struct stack *second = s->prev;
            long res = first->val + second->val;
            free(first);
            s = second->prev;
            free(second);
            s = newStack(res, s);
        }
        else if (strcmp(command, "SUB") == 0) {
            struct stack *first = s;
            struct stack *second = s->prev;
            long res = first->val - second->val;
            free(first);
            s = second->prev;
            free(second);
            s = newStack(res, s);
        }
        else if (strcmp(command, "MUL") == 0) {
            struct stack *first = s;
            struct stack *second = s->prev;
            long res = first->val * second->val;
            free(first);
            s = second->prev;
            free(second);
            s = newStack(res, s);
        }
        else if (strcmp(command, "DIV") == 0) {
            struct stack *first = s;
            struct stack *second = s->prev;
            long res = first->val / second->val;
            free(first);
            s = second->prev;
            free(second);
            s = newStack(res, s);
        }
        else if (strcmp(command, "MAX") == 0) {
            struct stack *first = s;
            struct stack *second = s->prev;
            long res = first->val > second->val ? first->val : second->val;
            free(first);
            s = second->prev;
            free(second);
            s = newStack(res, s);
        }
        else if (strcmp(command, "MIN") == 0) {
            struct stack *first = s;
            struct stack *second = s->prev;
            long res = first->val < second->val ? first->val : second->val;
            free(first);
            s = second->prev;
            free(second);
            s = newStack(res, s);
        }
        else if (strcmp(command, "NEG") == 0) {
            s->val = -s->val;
        }
        else if (strcmp(command, "DUP") == 0) {
            s = newStack(s->val, s);
        }
        else if (strcmp(command, "SWAP") == 0) {
            struct stack *first = s;
            struct stack *second = s->prev;
            first->prev = second->prev;
            second->prev = first;
            s = second;
        }
        scanf("%s", command);
    }
    printf("%ld", s->val);
    while (s != NULL){
        struct stack *prev;
        prev = s->prev;
        free(s);
        s = prev;
    }
    return 0;
}