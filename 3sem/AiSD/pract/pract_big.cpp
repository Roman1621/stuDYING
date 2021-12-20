#include "iostream"
#include "math.h"

using namespace std;

int numberOfDigits(int number){
    int n = 0;
    number = abs(number);
    
    do{
        number /= 10;
        n++;
    }while(number > 0);

    return n;
}

long long int* splitting(int number, int n, long long int* arr){
    if(number == 0)
        return 0;
    else{
        for(int i = (n-1); i>=0; i--){
            arr[i] = number%10;
            number /= 10;
        }
    }
    return arr;
}

int main(){
    cout << "Введите число" << endl;
    long long int number = 0;
    cin >> number;

    int n = 0;
    n = numberOfDigits(number);

    long long int* arr = new long long int[n];
    arr = splitting(number, n, arr);
    
    int big = 0;
    int i = 0;
    big = arr[i];
    for(;i < n; i++){
        if(big < arr[i])
            big = arr[i];
    }

    int low = 0;
    low = arr[i];
    for(; i > 0; i--){
        if(low > arr[i])
            low = arr[i];    
    }

    cout << "Наибольшая цифра числа: " << big << endl;
    cout << "Наименьшая цифра числа: " << low << endl;

    delete[] arr;
    return 0;
}