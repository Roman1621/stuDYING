#include <stdio.h>

#define MAXLINE 1000

int getl(char s[], int lim){
	int i, c;

	for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n'){
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	return i;
}

void entab(char to[], char from[]){
	int i, j, c, k, m, ns, nt;
	i = j = ns = nt = 0;

	while((c = from[i]) != '\0'){
		if (c == ' ')
			ns++;
		else if (ns > 0){
			nt = ns/3;
			for(m = 0; m < nt; m++){
				to[j] = '\t';
				j++;
			}
			for(k = 0; k < ns - nt*3; k++){
				to[j] = ' ';
				j++;
			}
			to[j] = c;
			j++;
			ns = 0;
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
	int len;
	char line[MAXLINE], newline[MAXLINE];

	while((len = getl(line, MAXLINE)) > 0){
		entab(newline, line);
		printf("%s", newline);
	}
	printf("\n");
	return 0;
}

