#include <iostream>
#include <cmath>

using namespace std;

double exponent(double number, int deg){
    number = fabs(number);
    double temp = number;
    if(deg == 0){
        number = 1;
        return number;
    }
    for(int i = 0; i < (deg-1); i++)
        number *= temp;
    return number;
}

int main(){
    cout << "Введите число: "; 
    double number = 0;
    cin >> number;

    cout << "Введите степень числа: ";
    int deg = 0;
    cin >> deg;

    double result = exponent(number, deg);
    cout << "Результат возведения в степень: " << result << endl;
    return 0;
}