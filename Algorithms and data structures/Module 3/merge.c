#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void sift_down(int *h_v, int *h_a_i, int h_s, int i) {
    int small = i, l = 2 * i + 1, r = 2 * i + 2;

    if (l < h_s && h_v[l] < h_v[small]) small = l;

    if (r < h_s && h_v[r] < h_v[small]) small = r;

    if (small != i) {
        swap(&h_v[i], &h_v[small]);
        swap(&h_a_i[i], &h_a_i[small]);
        sift_down(h_v, h_a_i, h_s, small);
    }
}

void add_to_heap(int *h_v, int *h_a_i, int *h_s, int v, int a_i) {
    int i = (*h_s)++;
    h_v[i] = v;
    h_a_i[i] = a_i;

    for (; i > 0 && h_v[(i - 1) / 2] > h_v[i]; i = (i - 1) / 2) {
        swap(&h_v[i], &h_v[(i-1)/2]);
        swap(&h_a_i[i], &h_a_i[(i-1)/2]);
    }
}

void remove_min(int *h_v, int *h_a_i, int *h_s) {
    h_v[0] = h_v[--(*h_s)];
    h_a_i[0] = h_a_i[*h_s];
    sift_down(h_v, h_a_i, *h_s, 0);
}

int main() {
    int k, h_s = 0, min_v, min_a_i;
    scanf("%d", &k);
    int *h_v, *h_a_i, *base, *sizes, *now_i;
    int **all[] = {&h_v, &h_a_i, &base, &sizes, &now_i};
    for (int i=0; i<5; i++) *all[i] = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) scanf("%d", &sizes[i]);

    base[0] = 0;
    for (int i = 1; i < k; i++) base[i] = base[i - 1] + sizes[i - 1];

    int elem_s = base[k - 1] + sizes[k - 1];
    int *elem = malloc(elem_s * sizeof(int));

    for (int i = 0; i < elem_s; i++) scanf("%d", &elem[i]);

    for (int i = 0; i < k; i++) {
        now_i[i] = 0;
        if (sizes[i] > 0) add_to_heap(h_v, h_a_i, &h_s, elem[base[i]], i);
    }

    while (h_s > 0) {
        min_v = h_v[0];
        min_a_i = h_a_i[0];
        remove_min(h_v, h_a_i, &h_s);
        printf("%d ", min_v);

        if (++now_i[min_a_i] < sizes[min_a_i]) {
            int next_v = elem[base[min_a_i] + now_i[min_a_i]];
            add_to_heap(h_v, h_a_i, &h_s, next_v, min_a_i);
        }
    }

    free(h_v);
    free(h_a_i);
    free(elem);
    free(base);
    free(sizes);
    free(now_i);

    return 0;
}