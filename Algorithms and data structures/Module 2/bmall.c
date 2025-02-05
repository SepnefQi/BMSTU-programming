#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max (int a, int b) {
    if (a > b) return a;
    return b;
}

void suffix(char *s, int *q, int ls) {
    int t = ls - 1;
    q[ls - 1] = t;
    for (int i = ls - 2; i >= 0; i--) {
        while (t < ls - 1 && s[t] != s[i]) t = q[t + 1];
        if (s[t] == s[i]) t--;
        q[i] = t;
    }
}

void delta1(char *s, int *d, int ls, int size, char b) {
    for (int i = 0; i < size; i++) d[i] = ls;
    for (int i = 0; i < ls; i++) d[s[i] - b] = ls - i - 1;
}

void delta2(char *s, int* z, int ls) {
    int q[ls];
    suffix(s, q, ls);
    int t = q[0];
    for (int i = 0; i < ls; i++) {
        while (t < i) t = q[t + 1];
        z[i] = ls + t - i;
    }
    for (int i = 0; i < ls - 1; i++) {
        t = i;
        while (t < ls - 1) {
            t = q[t + 1];
            if (s[i] != s[t]) z[t] = ls - i - 1;
        }
    }
}

void allsubstr(int* a, char *s, char *t, int ls, int lt, int size) {
    char b = 33; // !
    int d[size], z[ls], q = ls - 1, w = 0, e = 0, r, y;
    delta1(s, d, ls, size, b);
    delta2(s, z, ls);
    while (q < lt) {
        w = ls - 1;
        y = q + 1;
        r = e;
        while (t[q] == s[w]) {
            if (w == 0) {
                a[e] = q;
                e++;
            }
            w--;
            q--;
        }
        if (r < e) q = y;
        else q += max(d[t[q] - b], z[w]);
    }
}


int main(int argc, char** argv) {
    char* s = argv[1], *t = argv[2];
    int ls = strlen(s), lt = strlen(t);
    int a[lt], size = 94;
    for (int i = 0; i < lt; i++) a[i] = -1;
    allsubstr(a, s, t, ls, lt, size);
    for (int i = 0; a[i] != -1 && i < lt; i++) printf("%d ", a[i]);
    return 0;
}