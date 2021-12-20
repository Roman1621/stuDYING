#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 25
#define size 100

int main(){
    char *sentence;
    char symbol;
    int i = 0;
    sentence = (char*) malloc(size * sizeof(char));
    while (1){
        symbol = getchar();
        //Считывание символов при  условии, что они не цифры
        if (symbol != '0' && symbol != '1' && symbol != '2' && symbol != '3' && symbol != '4' && symbol != '5' && symbol != '6' && symbol != '7' && symbol != '8' && symbol != '9'){
            sentence[i] = symbol;
            i++;
        }
        //Выход из цикла при переполнении
        if (i == (N-2)){
            sentence[i+1] = '\0';
            printf("%s", sentence);
            break;
        }
        //Вывод символов на экран при отсутствии переполнения
        if (symbol == '\n'){
            symbol = '\0';
            printf("%s", sentence);
            break;
        }
    }
    free(sentence);
    return 0;
}
