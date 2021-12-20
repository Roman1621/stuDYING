#include <stdio.h>

int main(){
	int a, b;
	scanf("%d %d", &a, &b);
	if (a >= b){
		if (a>b){
			printf("%d\n", (a+b));
		}
		else printf("0\n");
	}
	else printf("%d\n", a*b);
	return 0;
}
