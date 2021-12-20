#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARR_SIZE 1000

void bubble_sort(int* arr){
	for(int i = 1; i < ARR_SIZE; i++){
		int k = i;
		while(k > 0 && arr[k-1] > arr[k]){
			int tmp = arr[k-1];
			arr[k-1] = arr[k];
			arr[k] = tmp;
			k--;
		}
	}
}

int comp(const void* a, const void* b){
	return(*(int*) a - *(int*) b);
}

int main(){
	clock_t t0, t1, t2;
	int arr[ARR_SIZE];
	int temp[ARR_SIZE];

	for(int i = 0; i < ARR_SIZE; i++){
		scanf("%d", &arr[i]);
		temp[i] = arr[i];
	}
	t0 = clock();
	bubble_sort(temp);
	t1 = clock() - t0;
	t0 = clock();

	qsort(arr, ARR_SIZE, sizeof(int), comp);
	t2 = clock() - t0;

	for(int i = 0;i < ARR_SIZE;i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	printf("%f\n", ((float)t1 / CLOCKS_PER_SEC));
	printf("%f\n", ((float)t2 / CLOCKS_PER_SEC));

	return 0;
}
