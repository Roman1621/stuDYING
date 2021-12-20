#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

float celsius(int a){
	return (a-32)*(5.0/9.0);
}

int main(){
	int fahr;

	for(fahr = LOWER; fahr <= UPPER; fahr += STEP)
		printf("%3d %6.1f\n", fahr, celsius(fahr));
	return 0;
}	
