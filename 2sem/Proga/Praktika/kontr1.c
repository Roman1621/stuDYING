#include <stdio.h>

int main(){
	unsigned int a, b;
	scanf("%x %x", &a, &b);
	if (a+b){
		return 1;
	}
	else{
		printf("%0\n", a+b);
	}
	return 0;
}
