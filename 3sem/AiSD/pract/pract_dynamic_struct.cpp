#include <iostream>
#include <cstring>

typedef struct Information{
    std::string name = "";
    int age = 0;
} Info;

int main(){
    std::cout << "Name: ";
    std::string name_temp = "";
    std::cin >> name_temp;
    std::cout << "Age: ";
    int age_temp = 0;
    std::cin >> age_temp;
    Info* Person_massive = new Info[1];
    Person_massive[0].name = name_temp;
    Person_massive[0].age = age_temp;
    std::cout << "Elements of struct Info: " << Person_massive[0].name << " " << Person_massive[0].age << "\n";

    int user_input = 0, size_of_massive = 1;
    std::cout << "One more person - 1, exit - 0: ";
    std::cin >> user_input;
    while(1){
        if(user_input == 1){
            std::cout << "Name: ";
            std::string name_temp2 = "";
            std::cin >> name_temp2;
            std::cout << "Age: ";
            int age_temp2 = 0;
            std::cin >> age_temp2;

            Info* copy_massive = new Info[size_of_massive];
            for(int i = 0; i < size_of_massive; i++){
                copy_massive[i].name = Person_massive[i].name;
                copy_massive[i].age = Person_massive[i].age;
            }
            delete[] Person_massive;

            Person_massive = new Info[size_of_massive+1];
            for(int i = 0; i < size_of_massive; i++){
                Person_massive[i].name = copy_massive[i].name;
                Person_massive[i].age = copy_massive[i].age;
            }
            Person_massive[size_of_massive].name = name_temp2;
            Person_massive[size_of_massive].age = age_temp2;
            delete[] copy_massive;
            size_of_massive++;

            for(int i = 0; i < size_of_massive; i++){
                std::cout << i << " element of struct: " << Person_massive[i].name << " " << Person_massive[i].age << std::endl;
            }
            std::cout << "One more person - 1, exit - 0: ";
            std::cin >> user_input;
            continue;
        }
        else if(user_input == 0){
            delete[] Person_massive;
            std::cout << "Exit!" << std::endl;
            return 0;
        }
        else{
            std::cout << "Incorrect data. Try again: ";
            std::cin >> user_input;
            continue;
        }
    }
}