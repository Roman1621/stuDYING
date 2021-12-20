#include <stdio.h>

//Определение функции discriminant
float discriminant(float a, float b, float c){
float f;
f = b*b - 4*a*c;
return f;
}

int main(){

float a, b, c;
float d;
scanf("%f %f %f", &a, &b, &c);
d = discriminant(a, b, c);
printf("%.0f\n", d);
return 0;
}

