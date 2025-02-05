#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Hash {
    int key;
    long long value;
    bool use; // использовалась ли сумма до этого
} Hash;

unsigned int hash(int key, int h) {
    return (unsigned int) key % h;
}


int main() {
    int n;
    long long s = 0, k=0;
    scanf("%d", &n);

    long long* a = calloc(n,  sizeof(long long));

    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);

    int h = 1 << 20;
    Hash *prefix_xor_count = calloc(h, sizeof(Hash));
    prefix_xor_count[0].key = 0;
    prefix_xor_count[0].value = 1;
    prefix_xor_count[0].use = true;


    for (int i = 0; i < n; i++) {
        k ^= a[i];

        unsigned int index = hash(k, h);

        while (prefix_xor_count[index].use &&
               prefix_xor_count[index].key != k) index = (index + 1) % h;

        if(prefix_xor_count[index].use){
            s += prefix_xor_count[index].value;
            prefix_xor_count[index].value++;
        } else {
            prefix_xor_count[index].key = k;
            prefix_xor_count[index].value = 1;
            prefix_xor_count[index].use = true;

        }
    }

    printf("%lld", s);

    free(a);
    free(prefix_xor_count);
    return 0;
}