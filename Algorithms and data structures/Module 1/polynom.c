#include <stdio.h>

int main() {
    long long n, x;
    scanf("%lld %lld", &n, &x);
    
    long long l[n + 1];
    scanf("%lld", &l[0]);
    
    long long P = l[0];
    for (long long i = 0; i < n; i++) {
        scanf("%lld", &l[i+1]);
        P = P*x + l[i+1];
    }
    long long Ppro1 = l[0]*n;
    
    for (long long i = 1; i < n; i++) {
        Ppro1 = Ppro1*x + l[i]*(n-i);
    }
    
    printf("%lld\n", P);
    printf("%lld\n", Ppro1);
    
    return 0;
}