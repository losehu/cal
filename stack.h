#include <string.h>
#define max_size 50
char stack[max_size][max_size];
short zhen;
void initstack() {
    memset(stack, 0, sizeof(stack));
    zhen = 0;
}
void push(char a[]) {
    strcpy(stack[zhen++], a);
}
void pop() {
    if (zhen)zhen--;
}
int isEmpty() {
    return zhen;
}
