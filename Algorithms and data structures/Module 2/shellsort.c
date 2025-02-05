void shellsort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j))
{
    unsigned long l, r, fib[nel+1], d=1, now;
    long long tl, tr;
    fib[0] = fib[1] = 1;
    while (fib[d] < nel) {
        d++;
        fib[d] = fib[d-1]+fib[d-2];
    }
    d--;
    for (l=0, now=fib[d]; d>0; d--, l=0, now=fib[d]) {
        for (r = now; r<nel; l++, r++) {
            for(tr=r, tl=l; tl>=0 && compare(tl, tr)==1; tr = tl, tl-=d) swap(tl, tr);
        }
    }
}