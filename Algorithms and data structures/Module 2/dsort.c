#include <stdio.h>

void key(char* s,int* keys,int n) {
    for (int i=0; i<n; i++) {
        keys[s[i]-'a']++;
    }
}

void distributionsort(const int* key,const char* s, int n, char* d) {
    int k, j=0, i=1, count[26] = {0};
    count[0] = key[0];
    while (i < 26) {
        count[i] = count[i - 1] + key[i];
        i++;
    }
    j = n-1;
    while (j >= 0) {
        k = s[j] - 'a';
        count[k]--;
        d[count[k]] = s[j];
        j--;
    }
}

int main() {
    int m = 1000001, n=0, keys[26] = {0};
    char s[m];
    fgets(s, m, stdin);
    while (s[n]!='\0' && s[n]!='\n' && s[n]!='\t') n++;
    char d[n+1];
    d[n] = '\0';
    key(s, keys, n);
    distributionsort(keys, s, n, d);
    printf("%s", d);
    return 0;
}