#include <stdio.h>
#define MAXLINE 50
#define LINERET 10
#define BORDER 5

int getl(char s[], int lim){
	int c, i;

	for(int i = 0; i<lim-1 && (c = getchar())!=EOF && c != '\n'; i++)
		s[i] = c;
	if(c == '\n'){
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	return i;
}

void filterret(char to[], char from[], int len){
	int c, i, j;
	j = 0;
	int start = 0;
	int cur_symb = 0;
	int temp = 0;

	while((len - cur_symb) > LINERET){
		cur_symb += LINERET;
		for(i = cur_symb - BORDER; i < cur_symb && (i+cur_symb) < len; ++i){
			c = from[i];
			if(c == ' ' || c == '\t' || c == '\n'){
				temp = i;
			}
		}
		if(temp > cur_symb - BORDER)
			cur_symb = temp + 1;
		for(i = start; i < (cur_symb - 1); i++, j++){
			to[j] = from[i];
		}
		to[cur_symb-1] = '\n';
		j++;
		start = cur_symb;
	}
	i = cur_symb;
	while((to[j] = from[i]) != '\0'){
		i++;
		j++;
	}
}

int main(){
	int len = 0;
	char line[MAXLINE];
	char newline[MAXLINE];

	while((len = getl(line, MAXLINE)) > 0){
		filterret(newline, line, len);
		printf("%s\n", newline);
	}

	return 0;
}
