#include <iostream>

int main(){
    unsigned long a = 0, b = 0;
    std::cout << "Enter numbers: ";
    std::cin >> a;
    std::cin >> b;

    while(a > 0 && b > 0){
        if(a > b) a %= b;
        else b %= a;
    }
    
    std::cout << "Result NOD: " << a+b << std::endl;
    return 0;
}