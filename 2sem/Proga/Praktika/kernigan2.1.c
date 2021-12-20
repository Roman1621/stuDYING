#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(){
	printf("%d <= int <= %d\n", INT_MIN, INT_MAX);
	printf("0 <= unsigned int <= %u\n", UINT_MAX);
	printf("%d <= char <= %d\n", CHAR_MIN, CHAR_MAX);
	printf("0 <= unsigned char <= %d\n", UCHAR_MAX);
	printf("%d <= signed char <= %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("%ld <= long <= %ld\n", LONG_MIN, LONG_MAX);
	printf("0 <= unsigned long <= %lu\n", ULONG_MAX);
	printf("%d <= short <= %d\n", SHRT_MIN, SHRT_MAX);
	printf("0 <= unsigned short <= %d\n", USHRT_MAX);
	printf("%f <= float <= %f\n", FLT_MIN, FLT_MAX);
	printf("%f <= double <= %f\n", DBL_MIN, DBL_MAX);
	return 0;
}

