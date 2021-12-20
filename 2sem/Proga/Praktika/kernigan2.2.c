#include <stdio.h>
#define MAXLINE 100

int main(){
	int i, c;
	i = 0;
	char line[MAXLINE];

	while(i < MAXLINE-1){
		c = getchar();
		if(c == EOF)
			break;
		if(c == '\n')
			break;
		line[i] = c;
		i++;
	}
	line[i] = '\0';
	printf("%s\n", line);
	
	return 0;
}

