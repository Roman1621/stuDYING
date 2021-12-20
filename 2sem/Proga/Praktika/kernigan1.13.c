#include <stdio.h>

#define WORD_LENGTH 20

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
	for(int i = 0; i < WORD_LENGTH; i++){
		if(i < 10)
			printf("length  %d: ", i);
		else
			printf("length %d: ", i);
		for(int j = 0; j < arr[i]; j++)
			printf("|");
		printf("\n");
	}
	return 0;
}

