#include <iostream>

int main(){
    std::cout << "Enter last number: ";
    unsigned int number = 0;
    std::cin >> number;
    unsigned int sum = 0;
    for(unsigned int i = 0; i <= number; i++){
        if((i%3) == 0 || (i%5) == 0) sum += i;;
    }
    std::cout << sum << std::endl;
    return 0;
}