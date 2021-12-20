#include <iostream>
#include <math.h>
using namespace std;

int sum_posl(int N, int k){
    int sum = 0;
    for(int i = 1; i <= N; i++){
        sum += pow(i, k);
    }
    return sum;
}

int main(){
    cout << "Введите N: ";
    int N = 0;
    cin >> N;

    cout << "Введите k: ";
    int k = 0;
    cin >> k;

    int sum = 0;
    sum = sum_posl(N, k);
    cout << sum << endl;

    return 0;
}