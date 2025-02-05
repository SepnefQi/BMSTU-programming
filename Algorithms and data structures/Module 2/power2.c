#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_power_of_two(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

void comb(int *a, int n, int in, int s, int *count) {
    if (is_power_of_two(s) && s != 0) (*count)++;

    for (int i = in; i < n; i++) {
        comb(a, n, i + 1, s + a[i], count);
    }
}

int main() {
    int n, count = 0;
    scanf("%d", &n);
    int a[n];

    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    comb(a, n, 0, 0, &count);

    printf("%d", count);

    return 0;
}