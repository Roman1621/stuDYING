#include <stdio.h>

#define IN 1
#define OUT 0

int main(){
	int a;
	int flag = OUT;
	while((a = getchar()) != EOF){
		if(a != ' ' && a != ',' && a != '.' && a != '\n' && a != '\t'){
			flag = IN;
			putchar(a);
		}
		else if(flag == IN){
			putchar('\n');
			flag = OUT;
		}
	}
	return 0;
}

