#include <stdio.h>

#define WORD_LENGTH 10

int main(){
	int c, lcw;
	int arr[WORD_LENGTH];

	for(int i = 0; i < WORD_LENGTH; i++)
		arr[i] = 0;

	while((c = getchar()) != EOF){
		if(c != ' ' && c != '.' && c != ',' && c != '\t' && c != '\n')
			lcw++;
		else{
			if(lcw > 0)
				arr[lcw] += 1;
			else if(lcw >= WORD_LENGTH)
				arr[0] += 1;
			lcw = 0;
		}
	}

	for(int i = 0; i < WORD_LENGTH; i++)
		printf("%d", i);
	printf("\n");

	int var = 1;
	while(var > 0){
		var = 0;
		for(int i = 0; i < WORD_LENGTH; i++){
			if (arr[i] > 0){
				printf("-");
				arr[i] -= 1;
			}
			else
				printf(" ");
			var += arr[i];
		}
		printf("\n");
	}
	return 0;
}

