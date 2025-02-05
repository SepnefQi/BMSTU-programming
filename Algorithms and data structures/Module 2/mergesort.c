#include <stdio.h>
#include <stdlib.h>

void insertion(int *a, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= l && abs(a[j]) > abs(key)) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

/* test:
5
   1   2   -1  -3  3   =>   1 -1 2 -3 3
5
   -1    -1     0    -1     0       =>   0 0 -1 -1 -1
7
    1     0     1     1     1    -1     1    => 0 1 1 1 1 -1 1
7
    1     0     1     0    -1     0     1    => 0 0 0 1 1 -1 1
5
   -2     3    -1    -2    -1        => -1 -1 -2 -2 3
*/


// Переписал из лекций
void merge(int *a, int l, int m, int r) {
    int n1 = r - l + 1;
    // a[k:l] + a[l+1:m]  ->  a[k:m]
    // a[l:m] + a[m+1:r]  ->  a[l:r]
    int t[n1];
    int i = l, j = m+1;
    for (int k=0; k < n1; k++) {
        if (j<=r &&  (i==(m+1) || (abs(a[j]) < abs(a[i])))) {
            t[k] = a[j++];
        } else {
            t[k] = a[i++];
        }
    }
    for (int i=l; i<=r; i++) a[i] = t[i-l];
}
void mergeSort(int *a, int l, int r) {
    if (r - l + 1 < 5) {
        insertion(a, l, r);
    } else {
        int mid = l + (r-l) / 2;
        mergeSort(a, l, mid);
        mergeSort(a, mid + 1, r);
        merge(a, l, mid, r);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    mergeSort(a, 0, n - 1);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    free(a);
    return 0;
}