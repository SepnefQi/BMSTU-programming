#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    double a[n];
    double q, w;
    for (int i=0; i<n; i++) {
        scanf("%lf%c%lf", &q, &w, &w);
        a[i] = q/w;
    }
    double k = 1.0, ma = 1.0;
    int l=0, r=0;
    for(int i=0; i<n-1; i++) { // [i : ...]
        k = 1.0;
        for (int j=i; j<n; j++) { // [i : j]
            k *= a[j];
            if (k>ma) {
                ma = k;
                l = i;
                r = j;
            }
        }
    }
    printf("%d %d", l, r);
    return 0;
}