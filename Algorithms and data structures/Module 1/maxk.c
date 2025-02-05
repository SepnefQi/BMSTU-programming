#include <stdio.h>

int main() {
    int n, k, maxs=0, nows=0;
    scanf("%d", &n);
    int a[n];
    for (int i=0; i<n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &k);
    for (int i=0; i<k; i++) {
        maxs += a[i];
    }
    nows = maxs;
    for (int i=k; i<n; i++) {
        nows -= a[i-k];
        nows += a[i];
        if (nows>maxs) maxs = nows;
    }
    printf("%d", maxs);
    return 0;
}