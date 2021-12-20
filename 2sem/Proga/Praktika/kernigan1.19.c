#include <stdio.h>
#define MAXLINE 1000

int getl(char s[], int lim){
	int c, i;

	for(i = 0;(i < lim - 1) && ((c = getchar()) != EOF) && c != '\n'; i++){
		s[i] = c;
	}
	if(c == '\n'){
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}

void reverse(char to[], char from[], int lim){
	int i;

	for(i = 0; i < lim - 1; i++)
		to[lim-2-i] = from[i];
	to[lim-1] = '\n';
	to[lim] = '\0';
}

int main(){
	int len = 0;
	char line[MAXLINE], newline[MAXLINE];

	while((len = getl(line, MAXLINE)) > 0){
		reverse(newline, line, len);
		printf("%s", newline);
	}
	printf("\n");
	return 0;
}

