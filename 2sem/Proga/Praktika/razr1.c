#include <stdio.h>
#define size 32

int main(){
    unsigned int n, count;
    count = 0;
    int bin[size];
    scanf("%d", &n);
    for(int i = 1; i <= size; i++)
    {
        bin[i] = n%2;
        n /= 2;
    }
    for(int i = 1; i <= size; i++){
	    if (bin[i] == 1) count++;
    }
    printf("%d\n", count);
    return 0;
}
