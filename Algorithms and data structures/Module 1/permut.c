#include <stdio.h>

int main() {
  int a[8], per, el, sall=0, s1=0;
  int ina[8];
  for (int i=0; i<8; i++){
    scanf("%d", &a[i]);
    ina[i] = 0;
  }
  for (int i=0; i<8; i++){
    s1 = 0;
    scanf("%d", &el);
    for (int i = 0; i < 8; i++) {
      if (el == a[i] && ina[i]==0) {
          s1 = 1;
          ina[i]=1;
          i = 8;
      }
    }
    if (s1) sall++;
  }
  if (sall==8) {
    printf("yes");
  } else {
    printf("no");
  }
  return 0;
}