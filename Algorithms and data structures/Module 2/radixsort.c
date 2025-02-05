#include <stdio.h>
#include <stdlib.h>

union Int32 {
    int x;
    unsigned char bytes[4];
};

void radixSort(union Int32 *a, int n) {
    int i, k;
    union Int32 *moment = calloc(n, sizeof(union Int32));

    for (k = 0; k < 4; k++) {
        int count[256] = {0};
        
        for (i = 0; i < n; i++) {
            int num = a[i].bytes[k];
            if (k<3) count[num]++;
            else count[(num+128)%256]++;
        }

        for (i = 1; i < 256; i++) count[i] += count[i - 1];

        for (i = n - 1; i >= 0; i--) {
            int num = a[i].bytes[k];
            if (k<3) moment[--count[num]] = a[i];
            else moment[--count[(num+128)%256]] = a[i];
        }

        for (i = 0; i < n; i++) a[i] = moment[i];
    }
    free(moment);
}

int main() {
    int n, i;
    scanf("%d", &n);

    union Int32 *a = calloc(n, sizeof(union Int32));
    for (i = 0; i < n; ++i) scanf("%d", &a[i].x);

    radixSort(a, n);

    for (i = 0; i < n; ++i) printf("%d ", a[i].x);
    free(a);
    return 0;
}