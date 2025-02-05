//Комментарий преподавателя: 👍
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    char *s = argv[1], *t = argv[2];//t из s?
    int sl = strlen(s), tl = strlen(t);
    int count[sl];
    count[0] = 0;
    for (int w=0, i=1; i<sl; i++) {//abracadabra
        while (w>0 && s[i] != s[w]) w = count[w-1];
        if (s[i]==s[w]) w++;
        count[i] = w;
    }
//1) count[1] = 0 4) count[4] = 0 7) count[7] = 1 10) count[10] = 4
//2) count[2] = 0 5) count[5] = 1 8) count[8] = 2
//3) count[3] = 1 6) count[6] = 0 9) count[9] = 3
    for (int k=0, q=0; k<tl; k++) {
        if (q==sl) q = count[q-1];
        if (s[q]==t[k]) {
            q++;
            continue;
        }
        int prefix_found=1;
        for(; q!=0 && s[q]!=t[k]; prefix_found = 0) q = count[q-1];
        k--;
        if (prefix_found) {
            printf("no");
            return 0;
        }
    }
    printf("yes");
    return 0;
}