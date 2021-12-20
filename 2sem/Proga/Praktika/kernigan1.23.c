#include <stdio.h>
#define MAXLINE 1000

int getl(char s[], int lim){
	int c, i;

	for(i = 0; i < lim-1 && (c = getchar()) != EOF; i++)
		s[i] = c;
	s[i] ='\0';
	return i;
}

void delcom(char to[], char from[]){
	int i, j;
	int foc, foq;

	foc = foq = 0;
	i = j = 0;
	while(from[j] != '\0'){
		if(from[j] == '"'){
			if(foq == 0)
				foq = 1;
			else
				foq = 0;
			to[i] = from[j];
			i++;
		}
		else if(from[j] == '/' && from[j+1] == '*' && foc == 0 && foq == 0){
			foc = 1;
			j++;
		}
		else if(from[j] == '*' && from[j+1] == '/' && foc == 1 && foq == 0){
			foc = 0;
			j++;
		}
		else if(foc == 0){
			to[i] = from[j];
			i++;
		}
		j++;
	}
}

int main(){
	int len = 0;
	char line[MAXLINE];
	char newline[MAXLINE];

	while((len = getl(line, MAXLINE)) > 0){
		delcom(newline, line);
		printf("%s", newline);
	}
	return 0;
}

