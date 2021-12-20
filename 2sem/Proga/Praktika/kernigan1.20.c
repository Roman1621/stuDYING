#include <stdio.h>

#define MAXLINE 1000

int getl(char s[], int lim){
	int i, c;

	for(i = 0; i < (lim - 1) && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n'){
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	return i;
}

void detab(char to[], char from[]){
	int c, i, j, k;
	i = j = 0;

	while((c = from[i]) != '\0'){
		if(c == '\t'){
			for(k = 0; k < 4; k++){
				to[j] = ' ';
				j++;
			}
		}
		else{
			to[j] = c;
			j++;
		}
		i++;
	}
	to[j] = '\0';
}

int main(){
	int len = 0;
	char line[MAXLINE], newline[MAXLINE];

	while((len = getl(line, MAXLINE)) > 0){
		detab(newline, line);
		printf("%s", newline);
	}
	printf("\n");
	return 0;
}

