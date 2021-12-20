#include <stdio.h>
#define size 8
int main()
{
    unsigned char n; int i;
    scanf("%hhu%d", &n, &i);

    unsigned char ones = ~0;
    ones >>= size-i;
    n = (n << i) | ones;
    printf("%u\n", n);
}
