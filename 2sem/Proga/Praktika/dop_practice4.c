#include <stdio.h>

int main(){
	int arr[15];
	int N = 0;
	do{
		scanf("%d", &arr[N]);
                N++;
	} while (N < 15 && getchar() != '\n');
	for (int j = 0; j < N; j++){
		printf("%d", arr[j]);
		printf(" ");
	}
	printf("\n");
	return 0;
}
