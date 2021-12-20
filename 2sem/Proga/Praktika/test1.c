#include <stdio.h>

int main(){
	int a, b;
	scanf("%d%d", &a, &b);
	float c = a/b;
	float d = b/a;
	printf("%f %f\n", c, d);
	return 0;
}
