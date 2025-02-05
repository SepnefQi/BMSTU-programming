#include <stdio.h>
#include <math.h>

int main() {
    unsigned long A = 0, B = 0, a, b, ka, kb;
    scanf("%lu", &a);
    for (int i=0; i<a; i++) {
        scanf("%lu", &ka);
        A += pow(2, ka);
    }
    scanf("%lu", &b);
    for (int i=0; i<b; i++) {
        scanf("%lu", &kb);
        B += pow(2, kb);
    }
    a = 0;
    while (A>0) {
        if (A%2==1 && B%2==1) printf("%lu ", a);
        a++;
        A /= 2;
        B /= 2;
    }
    return 0;
}
/*Пример:
A = 1 + 4 + 6 => 2 + 16 + 64 = 82
B = 2 + 3 + 4 + 5 => 4 + 8 + 16 + 32 = 60
1) A%2==0, B%2==0 => A = 41, B = 30
2) A%2==1, B%2==0 => A = 20, B = 15
3) A%2==0, B%2==1 => A = 10, B = 7
4) A%2==0, B%2==1 => A = 5, B = 3
5) A%2==1, B%2==1 => A = 2, B = 1 Вывод 4
6) A%2==0, B%2==1 => A = 0, B = 0 Конец
*/