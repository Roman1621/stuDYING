#include <stdio.h>
#define F 15

int main(){
	int A[F+2];
	int B[F];
	int N = 1;
	int i;
	while (getchar() != '\n' && N <= F){
		scanf("%d", &A[N]);
		N++;
	}
	A[-1] = 0;
	A[0] = A[-1];
	A[N] = 0;
	for (i = 1; i < N; i++){
		if (A[i-1] > A[i+1]){
			B[i] = A[i-1] * A[i+1];
			}
		else B[i] = A[i-1] + A[i+1];
	}
	for (i = 1; i < N; i++) printf("%d\t", B[i]);
	return 0;
}
