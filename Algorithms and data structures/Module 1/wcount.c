#include <stdio.h>
#include <stdlib.h>

int wcount (char *s) {
    long long k = 0;
    char new_word=1;
    for (int i=0; s[i]!='\0' && s[i] != '\n'; i++) {
        if ((s[i]!=' ' && s[i] != '\t')) {
            if (new_word) {
                k++; 
                new_word=0;
            }
        } else new_word = 1;
    }
    return k;
}

int main() {
    char* s = malloc(1000*sizeof(char));
    fgets(s, 1000, stdin);
    long long n = wcount(s);
    printf("%lld", n);
    free(s);
    return 0;
}
// s[i]!="\0" => #include <string.h> i<strlen(s)