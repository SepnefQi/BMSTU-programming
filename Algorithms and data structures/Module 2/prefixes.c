#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) a>b ? a : b

int pref(char *s, int ls, int end){
    for (int i = 0; i < ls; i++) {
        if (s[end - i] != s[ls - i - 1]) return 0;
    }
    return 1;
}

int main(int argc, char** argv) {
    char *s = argv[1];
    int ls = strlen(s);
    int a[ls+1];
    for (int i = 0; i < ls+1; i++) a[i] = 0;
    for (int i = 1; i < ls/2 + 1; i++) {
        for (int end = 2*i - 1; pref(s, i, end) && end < ls; end+=i) {
            a[end + 1] = max(a[end + 1], (end + 1) / i);
        }
    }
    for (int i = 0; i < ls+1; i++){
        if (a[i]) printf("%d %d\n", i, a[i]);
    }
    return 0;
}