#include <iostream>
#include <math.h>

using namespace std;

float new_element(float Z, float B, float A, float Betta){
    float X = 0;
    X = pow(Z, 3) - B + pow(A, 2)/(pow(tan(Betta), 2));
    return X;
}

int main(){
    cout << "Введите количество X: ";
    int number_of_X = 0;
    cin >> number_of_X;
    
    float Y = 0;
    float Z = 0, B = 0, A = 0, Betta = 0;
    float* array = new float[number_of_X];
    for(int i = 0; i < number_of_X; i++){
        cout << "Номер икса: " << i+1 << endl;
        
        cout << "Введите Z: ";
        cin >> Z;

        cout << "Введите B: ";
        cin >> B;

        cout << "Введите A: ";
        cin >> A;

        cout << "Введите Betta: ";
        cin >> Betta;

        array[i] = new_element(Z, B, A, Betta);
    }

    for(int i = 0; i < number_of_X; i++){
        Y += array[i];
    }

    cout << "Y = " << Y << endl;
    delete[] array;
    return 0;
}