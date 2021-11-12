#include <stdio.h>
#include "cal2.h"
void main() {
    while (1) {
        char d[30];
        char a[60];
        scanf("%s",d);
        exp_change(d, a);cut_plus(a);
          printf("%s\n", a);
    }
}
