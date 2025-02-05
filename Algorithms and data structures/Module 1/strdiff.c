int strdiff(char *a, char *b) {
    int res=0, i=0;
    int c1[8], c2[8];
    for (; !i || ((a[i-1]!='\0' && a[i-1]!='\n' && b[i-1]!='\0' && b[i-1]!='\n')); i++) {
        for (int j=0; j<8;  j++) {
            c1[j] = ((a[i]&(1<<j)) != 0);
            c2[j] = ((b[i]&(1<<j)) != 0);
            if (c1[j]!=c2[j]) return res;
            res++;
        }
    }
    if (a[i-1]==b[i-1]) return -1;
    return res;
}
