#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    char *s = argv[1];
    char *t = argv[2];
    int lens = strlen(s), lent = strlen(t);
    int** a = malloc(lens * sizeof(int*));
    
    for (int i=0; i<lens; i++) {
        a[i] = malloc(94 * sizeof(int));
        for (int j=0; j<94; j++) a[i][j] = i+1;
    }
    
    for (int i=0; i<lens; i++) {
        for (int j=i+1; j<lens && s[i] != s[j]; j++) a[j][s[i]-33] = j-i;
    }
    int i=0;
    for (int j=0, k=lens-1; j<=k && i<lent - lens + 1; j++, k--) {
        if (t[i+j] != s[j]) {
            i += a[j][t[i+j] - 33];
            j = -1;
            k = lens;
            continue;
        }
        if (t[i+k] != s[k]) {
            i += a[k][t[i+k] - 33];
            j = -1;
            k = lens;
            continue;
        }
    }
    
    if (i<lent-lens+1) {
        printf("%d", i);
    } else printf("%d", lent);
    
    for (int i=0; i<lens; i++) free(a[i]);
    free(a);
    return 0;
}