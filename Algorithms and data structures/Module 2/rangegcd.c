#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) {return (a==0 ? abs(b) : gcd(abs(b)%abs(a), abs(a)));}

int otv(int** s, int l, int r)
{
    return gcd(s[l][(int) log2(r - l + 1)], s[r - (1 << (int) log2(r - l + 1)) + 1][(int) log2(r - l + 1)]);
}

int** Build(int* a, int n)
{
    int m = log2(n) + 1;
    int** s = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        s[i] = (int*)malloc(m * sizeof(int));
        s[i][0] = abs(a[i]);
    }
    for (int j = 1, J = 1; j < m; j++) {
        J = J << 1;
        for (int i=0, Json = J >> 1; i <= n - J; i++) {
            s[i][j] = gcd(s[i][j - 1], s[i + Json][j - 1]);
        }
    }
    return s;
}

int main()
{
    int n, m, l, r;
    scanf("%d", &n);
    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    scanf("%d", &m);
    int** s = Build(a, n);
    for (int j = 0; j < m; j++) {
        scanf("%d%d", &l, &r);
        printf("%d\n", otv(s, l, r));
    }
    for (int i = 0; i < n; i++) free(s[i]);
    free(a);
    free(s);
    return 0;
}