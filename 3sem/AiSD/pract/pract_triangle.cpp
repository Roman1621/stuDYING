#include <iostream>
using namespace std;

void draw_right_triangle(int a){
    int k = 0;
    for(int i = 0; i < a, k < a; i++, k++){
        for(int j = 0; j <= k; j++){
            cout << "*";
        }
        cout << endl;
    }
}

int main(){
    int a = 0;
    cout << "Введите высоту и основание прямоугольного равнобедренного треугольника" << endl;
    cin >> a;
    draw_right_triangle(a);
    return 0;
}