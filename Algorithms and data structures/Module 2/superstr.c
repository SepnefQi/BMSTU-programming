#include <stdio.h>
#include <string.h>
#include <stdint.h>

int n, sl[10], minl = 2147483647;
char s[10][BUFSIZ], buffer[10*BUFSIZ];
uint8_t sel[10];
    
int find_sov(int l1, char* s1, int l2, char* s2) {
    int maxsov = l1 < l2 ? l1 : l2;
    while (maxsov && strncmp(s1 + l1 - maxsov, s2, (size_t)maxsov)) maxsov--;
    return maxsov;
}

void super(char* now, int nowl, int nown) {
    if (nown == n) {
        if (nowl < minl) minl = nowl;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!sel[i]) {
            sel[i] = 1;
            int sov = find_sov(nowl, now, sl[i], s[i]);
            strcat(now, s[i] + sov);
            super(now, nowl + sl[i] - sov, nown + 1);
            now[nowl] = '\0';
            sel[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
        sl[i] = (int)strlen(s[i]);
    }

    for (int i = 0; i < n; i++) {
        strcpy(buffer, s[i]);
        sel[i] = 1;
        super(buffer, sl[i], 1);
        sel[i] = 0;
    }
    printf("%d", minl);
    return 0;
}