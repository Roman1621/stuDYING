#include <iostream>
#include <fstream>

int main(){
    int checker_right = 0;
    int checker_left = -1;
    std::ofstream file_out("out.txt");
    std::ifstream file_in("in.txt");
    
    if(!file_in.is_open()){
        std::cout << "Файл не открыт" << std::endl;
        return 1;
    }
    else{
        while(!file_in.eof()){
            char symbol;
            file_in >> symbol;
            if(symbol == '{'){
                checker_right++;
                continue;
            }
            else if(symbol == '}'){
                checker_left++;
                continue;
            }
        }
    }

    if (checker_right == checker_left){
        file_out << "Баланс скобок не нарушен" << std::endl;
        std::cout << "Баланс скобок не нарушен" << std::endl;
    }
    else{
        file_out << "Баланс скобок нарушен";
        std::cout << "Баланс скобок нарушен" << std::endl;
    }
    //std::cout << checker_right << std::endl;
    //std::cout << checker_left << std::endl;

    file_out.close();
    file_in.close();
    return 0;
}