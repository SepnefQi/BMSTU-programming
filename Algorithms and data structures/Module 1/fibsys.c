#include <stdio.h>

int main() {
    long long F1=1, F2=1, x, fp, ma=1, k=1;//первые два числа фибоначчи равны 1
    scanf("%lld", &x);
    if (x==0) {
        printf("0");
    } else {
        while (F2<x) {//пока большее число фибоначчи меньше x
            ma++;
            fp = F2;
            F2 += F1;
            F1 = fp;//F1 => F2, F2 => F3
        }
        if (F2 > x) {//если большее число ф. больше x, то делаем 1 шаг назад
            ma--;
            fp = F1;
            F1 = F2 - F1;
            F2 = fp;//F2 => F1, F1 => F0 
        }
        for(;ma>0;ma--) {
            if (x==0) {
                printf("0");
            } else if (F2 <= x) {//если большее число фибоначчи меньше или равно x
                         //т.е. на месте этого i-ого числа будет стоять 1
                printf("1");
                k=1;
                x -= F2;//учли, что на его месте стоит 1
            } else if (F1>x && k==1){
                printf("0"); 
                fp = F1;
                F1 = F2 - F1;
                F2 = fp;
                fp = F1;
                F1 = F2 - F1;
                F2 = fp;
                k=0;
            } else if (k==0){
                printf("0");
                fp = F1;
                F1 = F2 - F1;
                F2 = fp;
                k=0;
            } else {
                fp = F1;
                F1 = F2 - F1;
                F2 = fp;
            }
        }
    }
    return 0;
}