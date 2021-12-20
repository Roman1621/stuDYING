#include <stdio.h>
#define REQ_LEN 80
#define MAXLEN 1000

int getl(char s[], int lim){
	int c;
	int i;

	for(i = 0; (i < (lim - 1)) && ((c = getchar()) != EOF) && (c != '\n'); i++)
		s[i] = c;
	if(c == '\n'){
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}

int main(){
	int len, last;
	char line[MAXLEN];

	len = 0;
	while((len = getl(line, MAXLEN)) > 0){
		last = line[len - 1];
		if((last == '\n') && len > REQ_LEN)
			printf("%s\n", line);
	}
	return 0;
}

