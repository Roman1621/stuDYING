#include <stdio.h>
#define MAXLINE 1000

int getl(char s[], int lim){
	int c, i;

	for(i = 0; i < (lim-1) && ((c = getchar()) != EOF) && c != '\n' ; i++)
		s[i] = c;
	if (c == '\n'){
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}

int filter(char to[], char from[]){
	int c;
	int i = 0;
	int j = 0;
	int flag = 0;

	while((c = from[i]) != '\n'){
		if(c == ' ' || c == '\t'){
			if(flag == 0){
				to[j] = ' ';
				flag = 1;
				j++;
			}
		}
		else{
			to[j] = c;
			flag = 0;
			j++;
		}
		i++;
	}

	if(c == '\n'){
		to[j] = c;
		j++;
	}
	to[j] = '\0';
	return j;
}

int main(){
	int len, last;
	char line[MAXLINE], newline[MAXLINE];

	len = 0;
	while((len = getl(line, MAXLINE)) > 0){
		if((len = filter(newline, line)) != 1)
			printf("%s", newline);		
	}
	printf("\n");
	return 0;
}

