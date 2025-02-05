#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) a>b ? a : b

struct a {
    struct a *parent;
    long value;
    struct a *left;
    struct a *right;
    long start;
    long end;
};

int type (struct a *a1, long i, long j) {
    return (a1->start <= i && a1->end >= i) || (a1->start <= j 
        && a1->end >= j) || (a1->start >= i && a1->end <= j);
}

long maxb(struct a *a1, long i, long j) {
    if ((a1->left == NULL && a1->right == NULL) || (i<= a1->start && j >= a1->end)) return a1->value;
    if (a1->right == NULL) return maxb(a1->left, i, j);
    long m1 = type(a1->left, i, j);
    long m2 = type(a1->right, i, j);
    if (m1 && m2) return max(maxb(a1->left, i, j), maxb(a1->right, i, j));
    return m1 ? maxb(a1->left, i, j) : maxb(a1->right, i, j);
}
int main() {
    int n;
    char s[5];
    scanf("%d", &n);
    struct a *as = calloc(n*4, sizeof(struct a));
    for(int i=0; i<n; i++) {
        scanf("%ld", &as[i].value);
        as[i].left = NULL;
        as[i].right = NULL;
        as[i].start = i;
        as[i].end = i;
    }
    int l = 0, r = n-1, end = n;
    while (r>l) {
        for (int i=l; i<=r; i+=2) {
            if (i==r) {
                as[end++].value = as[i].value;
                as[i].parent = &as[end - 1];
                as[end - 1].left = &as[i];
                as[end - 1].start = as[i].start;
                as[end - 1].end = as[i].end;
                continue;
            }
            as[end++].value = max(as[i].value, as[i+1].value);
            as[i].parent = &as[end - 1];
            as[i + 1].parent = &as[end - 1];
            as[end - 1].left = &as[i];
            as[end - 1].right = &as[i + 1];
            as[end - 1].start = as[i].start;
            as[end - 1].end = as[i + 1].end;
        }
        l = r+1;
        r = end-1;
    }
    as[--end].parent = NULL;
    scanf("%s", s);
    while (s[0] != 'E') {
        scanf("%d %d", &l, &r);
        if (s[0]=='M') printf("%ld\n", maxb(&as[end], l, r));
        else {
            struct a *second = &as[l];
            as[l].value = r;
            second = second->parent;
            while (second!=NULL) {
                if(second->right==NULL) {
                    second->value = second->left->value;
                    second = second->parent;
                    continue;
                }
                second->value = max(second->left->value, second->right->value);
                second = second->parent;
            }
        }
        scanf("%s", s);
    }
    free(as);
    return 0;
}