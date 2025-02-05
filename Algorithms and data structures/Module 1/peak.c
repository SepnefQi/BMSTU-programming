#include <stdio.h>

unsigned long peak(unsigned long nel, int (*less)(unsigned long i, unsigned long j)) {
    int w=1, ma=0;
    for (;w<(nel-1);w++) if (!(less(w, w-1)) && !(less(w, w+1))) ma=w;
    if (nel>1){
        if (!less(nel-1, nel-2)) ma=(nel-1);
    }
    return ma;
}