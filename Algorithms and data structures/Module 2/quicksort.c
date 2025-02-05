#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *base, size_t i, size_t j) {
    if (base[i] != base[j]) {
        base[i] ^= base[j];
        base[j] ^= base[i];
        base[i] ^= base[j];
    }
}

void heapify(int *base, size_t nowi, size_t as) {
    while (1) {
        size_t l = 2 * nowi + 1;
        size_t r = l + 1;
        size_t mi = nowi;
        if (l < as && base[nowi] < base[l]) nowi = l;
        if (r < as && base[nowi] < base[r]) nowi = r;
        if (nowi == mi) break;
        swap(base, nowi, mi);
    }
}

void build_heap(void *base, size_t as) {
    long long i = (as / 2) - 1;
    for (i; i >= 0; i--) heapify(base, i, as);
}

void hsort(void *base, size_t as) {
    if (as > 1) {
        build_heap(base, as);
        long long i = as - 1;
        for (i; i > 0; i--) {
            swap(base, 0, i);
            heapify(base, 0, i);
        }
    }
}

void selsort(int *base, size_t as) {
    for (size_t i = 0; i < as; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < as; j++) {
            if (base[min_index] > base[j]) min_index = j;
        }
        if (min_index != i) swap(base, min_index, i);
    }
}

size_t partition(int *base, size_t l, size_t r) {
    size_t border = l;
    for (size_t i = l; i < r-1; i++) {
        if (base[i] < base[r-1]) {
            swap(base, i, border);
            border++;
        }
    }
    swap(base, border, r-1);
    return border;
}

void quicksortrec(int *base, size_t l, size_t r, size_t k, int depth) {
    if (r - l < k) {
        selsort(base + l, r - l);
    } else if (depth <= 0) {
        hsort(base + l, r - l);
    } else if (l + 1 < r) {
        size_t border = partition(base, l, r);
        quicksortrec(base, l, border, k, depth-1);
        quicksortrec(base, border + 1, r, k, depth-1);
    }
}

void quicksort(int *base, size_t as, size_t k) {
    quicksortrec(base, 0, as, k, log10(as));
}

int main(int argc, char **argv) {
    size_t n, m;
    scanf("%lu", &n);
    scanf("%lu", &m);
    int *a = (int *)calloc(n, sizeof(int));
    for (size_t i = 0; i < n; i++) scanf("%i", &a[i]);
    quicksort(a, n, m);
    for (size_t i = 0; i < n; i++) printf("%i\n", a[i]);
    free(a);
    return 0;
}