#include <stdio.h>

int main(){
//	int i;
	long j;
	short k;
//	for(i = 1; i != 0;i++){
//		if(i < 0)
//			break;
//	}
//	printf("MIN: %d\n", --i);
//	printf("MAX: %d\n", i);
	for(j = 1; j != 0; j++){
		if(j < 0)
			break;
	}
	printf("MIN: %ld\n", --j);
        printf("MAX: %ld\n", j);
	for(k = 1; k != 0; k++){
		if(k < 0)
			break;
	}
	printf("MIN: %d\n", --k);
        printf("MAX: %d\n", k);
	return 0;
}
