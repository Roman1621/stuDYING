#include <iostream>
#include <cmath>

const double G = 9.8;
const double Pi = 3.14156;

using namespace std;

double angle_func(int time, int speed){
    double angle = asin((G*time)/(2*speed));
    return angle;
}

int main(){
    cout << "Введите Т: " << endl;
    int T = 0;
    cin >> T;

    cout << "Введите V: " << endl;
    int V = 0;
    cin >> V;

    if(fabs((G*T)/(2*V)) > 1.0)
        cout << "Неккоректный ввод" << endl;
    else{
        double angle = angle_func(T, V);
        cout << "Угол равен: " << (90/Pi) * angle << endl;
    }
    return 0;
}