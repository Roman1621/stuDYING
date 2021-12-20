#include <iostream>

int main(){
    int user_input = 0;
    int* arr = new int[1];
    int* copy_arr = nullptr;
    

    int counter = 0;
    while(1){
        std::cout << "Введите число: ";
        std::cin >> user_input;
        
        if(user_input < 0) break;

        if(counter == 0){
            arr[0] = user_input;
            std::cout << arr[0] << std::endl;
            counter++;
        }
        else{

     /*   if(counter = 0 && user_input >= 0){
            arr[0] = user_input;
            counter++;
            std::cout << arr[0] << std::endl;
            continue;
        }
*/
            copy_arr = new int[counter+1];
            for(int i = 0; i < counter; i++){
                copy_arr[i] = arr[i];
            }
            copy_arr[counter] = user_input;
            delete[] arr;

            arr = new int[counter+1];
            for(int i = 0; i < (counter+1); i++){
                arr[i] = copy_arr[i];
            }
            delete[] copy_arr;

            for(int i = 0; i < (counter+1); i++){
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
            counter++;
        }
    }
    
    delete[] arr;
    return 0;
}