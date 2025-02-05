#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat(char **s, int n) {
    int l = 0;
    for (int i=0; i<n; i++) {
        l += strlen(s[i]);
    }
    char *result = (char *)malloc(l+1);
    int pos = 0;
    for (int i=0; i<n; i++) {
        strcpy(result + pos, s[i]);
        pos += strlen(s[i]);
    }
    result[l] = '\0';
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    char **result = (char **)malloc(n * sizeof(char *));
    for (int i=0; i<n; i++) result[i] = (char *)malloc(1005 * sizeof(char)); 
    for (int i=0; i<n; i++) scanf("%s", result[i]); 
    char *s = concat(result, n);
    printf("%s", s);
    for (int i=0; i<n; i++) {
        free(result[i]);
    }
    free(result);
    free(s); 
    return 0;
}