#include <iostream>
#include <math.h>
#include <cassert>
using namespace std;

float discr(float a, float b, float c){
	float d = b*b - 4*a*c;

	if(d < 0){
		d = -1.0;
		return d;
	}
	else return d;
}

int main(){
	cout << "Введите коэфициенты квадратного уравнения" << endl;
	float a = 0.0, b = 0.0, c = 0.0, d = 0.0;
	cin >> a;
	cin >> b;
	cin >> c;
	cin >> d;
	c -= d;

	if(a == 0 && b == 0){
		cout << "Некорректные коэфициенты" << endl;
		return 0;
	}
	if(a == 0){
		float x = ((-1)*c)/b;
		cout << "Это не квадратичное решение, но решение следующее: " << x << endl;
		return 0;
	}
	float x1 = 0.0, x2 = 0.0;
	float dis = discr(a, b, c);
	if(dis == -1.0) {
		cout << "Уравнение не имеет решений" << endl;
		return 0;
	}
	else if(dis == 0.0){
		x1 = x2 = ((-1)*b)/(2*a);
		cout << "Уравнение имеет один корень: " << x1 << endl;
		return 0;
	}
	else{
		x1 = ((-1)*b + sqrt(dis))/(2*a);
		x2 = ((-1)*b - sqrt(dis))/(2*a);
		cout << "Уравнение имеет два корня: " << x1 << " " << x2 <<endl;
		return 0;
	}
}
