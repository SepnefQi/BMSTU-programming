#include <stdio.h>

void bubblesort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j)) {
    if (nel>=1) {
        unsigned long l, r;
        for (l=1, r=nel-1; l <= r; r--) {
            for (int i = r; i >= l; i--) {
                if (compare(i-1, i) == 1) {
                    swap(i-1, i);
                }
            }
            l++;
            for (int i = l; i <=r; i++) {
                if (compare(i-1, i) == 1) {
                    swap(i-1, i);
                }
            }
        }
    }
}