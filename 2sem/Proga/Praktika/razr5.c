#include <stdio.h>

int main()
{
    unsigned short n;
    int i;
    scanf("%hu%d", &n, &i);
    unsigned short erase_bit = ~(1 << i); //создание строки для замены битов
    unsigned short stable_bit = n & (1 << i); //создание строки для сохранения стабильного бита
    n = (~n) & erase_bit | stable_bit; 
    printf("%u\n", n);
}
