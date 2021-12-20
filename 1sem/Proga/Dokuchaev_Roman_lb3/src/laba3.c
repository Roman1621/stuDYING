#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size_sent 100

int main(){
	char* sentence;
	char symbol;
	int n = 0, m = 0, a = 0, i = size_sent;	
	//Выделяем память под предложение
	sentence = (char*) malloc(size_sent * sizeof(char));
	while (1){
		//Считываем первый символ
		symbol = getchar();
		//Пропуск табуляций и пробелов
		while (symbol == '\t' || symbol == ' '){
			symbol = getchar();
		}
		
		while (symbol != '.' && symbol != ';' && symbol != '?' && symbol != '!' ){   //Считываем посимвольно предложения из исходного текста
			sentence[a] = symbol;
			a++;
			if (a >= i - 2){                   //Текущий индекс вышел за размер буфера => увеличиваем память
				i += size_sent;
				sentence = (char*) realloc(sentence, i * sizeof(char));
			}
			symbol = getchar();
		}
		sentence[a] = symbol;
		sentence[a + 1] = '\0'; //Записываем последний символ в предложений
		//Выходим из цикла, если 
		if (symbol == '!'){
			printf("%s\n", sentence);
			break;
		}
		//Подсчёт предложений после редактирования и вывод предложений, которые заканчиваются не на вопросительный знак
		if (symbol == '.' || symbol == ';'){ 
			m++;
			printf("%s\n", sentence);
		}
		//Подсчёт предложений до редактирования
		n++;
		a = 0;
	}
	printf("Количество предложений до %d и количество предложений после %d\n", n, m); //Вывод количества предложений
	free(sentence);
	return 0;
}
