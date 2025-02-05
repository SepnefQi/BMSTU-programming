//Комментарий преподавателя: Одобряю дерево Фенвика!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *a;
int n;

int is_peak(int a[], int i, int n) {
    return (0<=i && i<n) && (i>0 ? a[i-1]<=a[i] : 1) && (i<n-1 ? a[i+1]<=a[i] : 1);
}

int count_peaks(int *arr, int left, int right) {
    int count = 0;
    for (int i=right; i>=0; i = (i & (i+1)) - 1) count += arr[i];
    for(int i=left-1; i>=0; i = (i & (i+1)) - 1) count -= arr[i];
    return count;
}

void update(int *arr, int i, int value, int n) {
    for(; 0<=i && i<n; i |= (i+1)) arr[i] += value;
}

int main() {
    scanf("%d", &n);

    a = calloc(n, sizeof(int));
    
    int b[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
    
    for (int i=0; i<n; i++) update(a, i, is_peak(b, i, n), n);

    char command[10];
    
    while (1) {
        scanf("%s", command);
        
        if (strcmp(command, "END") == 0) {
            break;
        } else if (strcmp(command, "PEAK") == 0) {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%d\n", count_peaks(a, l, r));
        } else if (strcmp(command, "UPD") == 0) {
            int i, v;
            scanf("%d %d", &i, &v);
            int b1 = is_peak(b, i - 1, n), b2 = is_peak(b, i, n), 
                b3 = is_peak(b, i + 1, n);
            b[i] = v;
            update(a, i - 1, is_peak(b, i - 1, n) - b1, n);
            update(a, i, is_peak(b, i, n) - b2, n);
            update(a, i + 1, is_peak(b, i + 1, n) - b3, n);
        }
    }

    free(a);

    return 0;
}