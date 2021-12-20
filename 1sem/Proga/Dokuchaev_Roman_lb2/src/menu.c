#include <stdio.h>
#include <stdlib.h>

#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

#define N 20

int main(){
	int n = 0, key;
	int arr[N];
	scanf("%d" , &key);
	while (getchar() != '\n' && n < N){
		scanf("%d", &arr[n]);
		n ++;
	}

	switch(key){
		case 0:
			printf("%d\n", index_first_negative(arr, n));
			break;
		case 1:
			printf("%d\n", index_last_negative(arr, n));
			break;
		case 2:
			printf("%d\n", multi_between_negative(arr, n));
			break;
		case 3:
			printf("%d\n", multi_before_and_after_negative(arr, n));
			break;
		default:
			puts("Данные некорректны");
			break;
	}
	return 0;
}
