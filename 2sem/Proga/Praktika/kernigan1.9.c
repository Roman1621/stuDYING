#include <stdio.h>

int main(){
	int a;
	int comporator = 0;
	while((a = getchar()) != EOF){
		if (a == ' \n' && a == '  \n'){
			a = ' ';
		}
		comporator++;
		putchar(a);
	}
	return 0;
}

