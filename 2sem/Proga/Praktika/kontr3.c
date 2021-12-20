#include <stdio.h>

int main(){
    int N;
    int sum = 0;
    scanf("%d", &N);
    unsigned int arr[N];
    int i = 0;
    while (getchar() != '\n' || i < N){
	    scanf("%d", &arr[i]);
	    i++;
    }
    for (int n = 0; n<N; n += 2){
	    sum += arr[n];
    }
    printf("%d\n", sum);
    return 0;
}
