#include <stdio.h>

#define CODE1 "\033[32;43m"
#define NONE "\033[0m"

int main()
{
	printf("%sHello\n", CODE1, NONE);
	return 0;
}
