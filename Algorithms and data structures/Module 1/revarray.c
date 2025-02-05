#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void revarray(void *base, size_t nel, size_t width) {
    char *os = malloc(width);
    for (int i=0; i<nel/2; i++) {
        char *l = (char*)base + i * width;
        char *r = (char*)base + (nel - i - 1) * width;
        memcpy(os, l, width);
        memcpy(l, r, width);
        memcpy(r, os, width);
    }
    free(os);
}