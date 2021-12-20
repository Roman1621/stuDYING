#include <iostream>
#include <math.h>
using namespace std;

int numberOfDigits(int number){
    int temp = 0;
    temp = abs(number);
    int n = 0;

    do{
	temp /= 10;
	n++;
    }while(temp > 0);
    cout << "Количество цифр в числе: " << n << endl;
    return n;
}

int splitRec(int number, int n){
	if(n == 0){
		return 0;
	}	
	else{
		cout << "Разряд " << n << " исходного числа равен: " << number%10 << endl;
		number /= 10;
		splitRec(number, n-1);
	}
    return 0;
}

int main(){
    cout << "Введите желаемое число: " << "\n";
    int number = 0;
    cin >> number;

    int n = 0;
    n = numberOfDigits(number);

    splitRec(number, n);
    return 0;
}
