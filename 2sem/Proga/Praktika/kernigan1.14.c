#include <stdio.h>
#include <ctype.h>

#define LENGTH 37

int main(){
	int c;
	int arr[LENGTH];

	for(int i = 0; i < LENGTH; i++)
		arr[i] = 0;

	while((c = getchar()) != EOF){
		if(c >= '0' && c <= '9')
			++arr[c-'0'];
		else if (c == '.' || c == ',' || c == ' ' || c == '\t' || c == '\n')
			++arr[10];
		else if (tolower(c) >= 'a' && tolower(c) <= 'z')
			++arr[tolower(c) - 'a' + 10];
		else
			printf("Wwedi normalnyi stroku!!!!!!!!!\n");
	}

	for(int i = 0; i < LENGTH; i++){
		if(i < 10)
			printf("%d", i);
		else if(i == 10)
			printf("s");
		else
			printf("%c", ('a' + i - 10));
		for(int j = 1; j <= arr[i]; j++)
			printf("|");
		printf("\n");
	}
	return 0;
}

