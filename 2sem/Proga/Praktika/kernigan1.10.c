#include <stdio.h>

int main(){
	int a;
	while((a = getchar()) != EOF){
		if (a == '/')
			printf("//");
		else if (a == '\t')
			printf("t");
		else if (a == '\b')
			printf("b");
		else
			putchar(a);
	}
	return 0;
}

