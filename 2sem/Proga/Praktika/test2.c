#include <stdio.h>

//---Реализуйте функцию f здесь
int f(int a, int b, int c){
    int f;
f = a;
if(b>f) f = b;
if (c>f) f = c;
return f;
}

int main(){
    char a,b,c;
    scanf("%c %c %c",&a,&b,&c);
    printf("%c", f(a,b,c));
    return 0;
}
