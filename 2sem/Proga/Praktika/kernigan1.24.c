#include <stdio.h>
#include <math.h>
#define MAXLINE 1000

int getl(char s[], int lim){
	int i, c;

	for(i = 0; i < lim - 1 && (c = getchar()) != EOF; i++)
		s[i] = c;
	s[i] = '\0';
	return i;
}

void sintaxis(char line[]){
	int i, c;
	i = 0;
	char prev;
	int rbf, cbf, sbf, cf, sqf, dqf; //Круглые скобки, фигурные скобки, квадратные скобки, комментарий, одинарные кавычки, двойные кавычки
	rbf = cbf = sbf = cf = sqf = dqf = 0;

	while((c = line[i]) != '\0'){
		if(prev == '/' && c == '*' && sqf == 0 && dqf == 0)
			cf++;
		else if(prev == '*' && c == '/' && sqf == 0 && dqf == 0)
			cf--;
		if(c == '"' && sqf == 0 && cf == 0)
			dqf++;
		else if(c == '"' && dqf>0 && cf == 0 && sqf == 0)
			dqf--;
//		if(prev != * && c == '\* && cf == 0 && dqf == 0)
//			sqf++;
//		else if(prev != '' && c == '\* && sqf > 0 && cf == 0 && dqf == 0)
//			sqf--;
		if(c == '(' && cf == 0 && sqf == 0 && dqf == 0)
			rbf++;
		if(c == ')' && cf == 0 && sqf == 0 && dqf == 0)
			rbf--;
		if(c == '[' && cf == 0 && sqf == 0 && dqf == 0)
			sbf++;
		if(c == ']' && cf == 0 && sqf == 0 && dqf == 0)
			sbf--;
		if(c == '{' && cf == 0 && sqf == 0 && dqf == 0)
			cbf++;
		if(c == '}' && cf == 0 && sqf == 0 && dqf == 0)
			cbf--;
		prev = c;
		i++;
	}
	if(cf != 0)
		printf("Не закрытых комментариев %d\n", abs(cf));
	else
		printf("Все комментарии закрыты\n");
	if(sqf != 0)
		printf("Не закрытых одинарных кавычек %d\n", abs(sqf));
	else
		printf("Все одинарные кавычки закрыты\n");
	if(dqf != 0)
		printf("Не закрытых двойных кавычек %d\n", abs(dqf));
	else
		printf("Все двойные кавычки закрыты\n");
	if(rbf > 0)
		printf("Не закрыты ( %d\n", rbf);
	else if(rbf < 0)
		printf("Не закрыты ) %d\n", -rbf);
	if(sbf > 0)
                printf("Не закрыты [ %d\n", sbf);
        else if(sbf < 0)
                printf("Не закрыты ] %d\n", -sbf);
	if(cbf > 0)
                printf("Не закрыты } %d\n", cbf);
        else if(cbf < 0)
                printf("Не закрыты } %d\n", -cbf);
}

int main(){
	int len;
	char line[MAXLINE];

	while((len = getl(line, MAXLINE)) > 0)
		sintaxis(line);

	return 0;
}

