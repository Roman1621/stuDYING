#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int arr[], int n){
	int i = 0;
	int um_before_and_after = 1;
	for (i = 0; i < index_first_negative (arr, n); i++) um_before_and_after *= arr[i];
	for (i = index_last_negative (arr, n); i < n; i++) um_before_and_after *= arr[i];
	return um_before_and_after;
}
