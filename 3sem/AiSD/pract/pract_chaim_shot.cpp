#include <iostream>

using namespace std;

int main(){
    int number = 0;
    cout << "Введите число для цепной дроби: ";
    cin >> number;

    double result = 0.0;
    if(number == 0){
        cout << result << endl;
        return 0;
    }
    else if(number == 1){
        result = 1;
        cout << result << endl;
        return 0;
    }
    else if(number == 2){
        result = 1.5;
        cout << result << endl;
        return 0;
    }

    double temp = 1.5;
    result = 1.0;
    for(int i = 2; i < number; i++){
        result = 1.0 + (1.0/temp);
        temp = result;
    }

    cout << result << endl;
    return 0;
}