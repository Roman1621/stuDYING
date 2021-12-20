#include <stdio.h>
#define MAX_LENGTH 1000

int getl(char s[], int lim){
	int c;
	int i;

	for(i = 0; (i < (lim - 1)) && ((c = getchar()) != EOF) && (c != '\n'); i++)
		s[i];
	if(c == '\n'){
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}

void copy(char to[], char from[]){
	int i = 0;
	while((to[i] = from[i]) != '\0')
		i++;
}

int main(){
	int len, max, temp;
	char line[MAX_LENGTH], longest[MAX_LENGTH];
	max = 0;
	len = 0;

	while((temp = getl(line, MAX_LENGTH)) > 0){
		len += temp;
		if(temp != (MAX_LENGTH - 1)){
			if(len > max){
				max = len;
				copy(longest, line);
			}
			len = 0;
		}
	}

	if(max > 0)
		printf("%d\n", max);
	return 0;
}

