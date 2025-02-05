#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alg_KMP(char *s, int *pi, int s1) {
    pi[0] = 0;
    int q = 0;
    for (int k = 1; k < s1; k++) {
        while (q > 0 && s[k] != s[q]) q = pi[q - 1];
        if (s[q] == s[k]) q++;
        pi[k] = q;
    }
}


int main(int argc, char *argv[]) {
    char *s = argv[1], *t = argv[2];

    int s1 = strlen(s), t1 = strlen(t), q=0;

    if (s1 == 0 || t1 == 0) return 0;

    int *k = calloc(s1, sizeof(int));

    alg_KMP(s, k, s1);

    for (int i = 0; i < t1; i++) {
        while (q > 0 && s[q] != t[i]) q = k[q - 1];
        if (s[q] == t[i]) q++;
        if (q == s1) {
            printf("%d ", i - s1 + 1);
            q = k[q - 1];
        }
    }
    free(k);
    return 0;
}