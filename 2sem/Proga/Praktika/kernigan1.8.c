#include <stdio.h>

int main(){
	int c, special_symbol;
	special_symbol = 0;

	while((c = getchar()) != EOF){
		if (c == '\n' || c == '\t' || c == ' '){
			++special_symbol;
		}
	}
	printf("%d\n", special_symbol);
	return 0;
}

