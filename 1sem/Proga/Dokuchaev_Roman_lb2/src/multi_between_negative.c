#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int arr[], int n){
	int i = 0;
	int um_between = 1;
	for(i = index_first_negative (arr, n); i < index_last_negative (arr, n); i++){
		um_between *= arr[i];
	}
	return um_between;
}
