#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%i %i", &n, &m);
    int a[n][m], ma[n], mi[m];
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            scanf("%i", &a[i][j]);
            ma[i] = 0;
            mi[j] = 0;
        }
    }
    //У нас n(i) строк и m(j) столбцов
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            k = a[i][j];
            if (k>a[i][ma[i]]) ma[i] = j;
            if (k<a[mi[j]][j]) mi[j] = i;
        }
    }
    for (int i=0; i<n; i++) {
        if (mi[ma[i]] == i) {
            printf("%i %i", i, ma[i]);
            return 0;
        }
    }
    printf("none");
    return 0;
}