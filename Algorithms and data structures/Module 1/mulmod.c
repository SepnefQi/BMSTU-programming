#include <stdio.h>

int main() {
    unsigned long long a, b, m;
    scanf("%lld %lld %lld", &a, &b, &m);
    
    char st[65];
    int index = 0;
    
    for (int i = 0; i < 64; i++) {
        st[i] = '0';
    }
    st[64] = '\0';

    while (b) {
        st[index++] = (b % 2) + '0';
        b = b/2;
    }

    for (int i = 0; i < 32; i++) {
        char temp = st[i];
        st[i] = st[63 - i];
        st[63 - i] = temp;
    }

    unsigned long long otv = (a * (st[0] - '0') * 2);
    for (int i = 1; i < 63; i++) {
        otv = (((otv + a * (st[i] - '0') % m) % m)* 2) % m;
    }

    otv = (otv + a * (st[63] - '0')) % m;

    printf("%lld\n", otv);

    return 0;
}