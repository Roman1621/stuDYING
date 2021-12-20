#include <stdio.h>
#define MAXLINE 80

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

int main(){
      int len; /* длина текущей строки */
      int cont; /* продолжать ли расчет? */
      int last;
      char line[MAXLINE]; /* текущая строка */

      len = 0;
      cont = 0;
      while ((len = getl(line, MAXLINE)) > 0) {
          last = line[len-1];
          if (len == MAXLINE-1) {
              printf("%s", line);
              cont = 1;
          }
          else if (cont == 1) {
              printf("%s\n", line);
              cont = 0;
          }
      }
      return 0;
}
