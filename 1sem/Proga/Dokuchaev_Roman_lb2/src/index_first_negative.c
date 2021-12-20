#include "index_first_negative.h"

int index_first_negative(int arr[], int n){
	int first_negative;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (arr[i] < 0)
			break;
	}
	return i;
}
