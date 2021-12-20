#include <stdio.h>

// Функция ничего не принимает и всегда возвращает 5
int getFive(){
return 5;
}

// Функция, которая считает сумму аргументов
int sum(int a, int b){
int res; 
res = a + b;
return res;
}

//Функция, которая ничего не возвращает и печатает на экран ее аргумент
void printInt(int num){
printf("printing number: %d\n", num);
}
int main(){
int n1, n2, s;
n1 = getFive();
printInt(n1);
s = sum(getFive(), 10);
printInt(s);
return 0;
}





