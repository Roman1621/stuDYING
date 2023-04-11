#include <iostream>

int main(){
    int size = 0;
    std::cout << "Введите размер массива: ";
    std::cin >> size;

    int massive[size][size];
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            massive[i][j] = 0;
    }

    massive[0][0] = 1;
    massive[size-1][size-1] = size*size;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(j == 0 && ((i%2) == 1)) massive[i][j] = massive[i-1][j] + 1;
            else if(j == 0 && ((i%2) == 0) && i != 0) massive[i][j] = massive[i-1][j] + 4*(i/2);
            
            if(i == 0 && j%2 == 1)massive[i][j] = massive[i][j-1] + 2 + 4*(j/2);
            else if(i == 0 && j%2 == 0 && j != 0) massive[i][j] = massive[i][j-1] + 1;
            
            //if(i == size-1 && j%2 == 0 && j != size-1)massive[i][j] = massive[i][j+1] - 2 - 4*((size-j-1)/2);
            //else if(i == size-1 && j%2 == 1 && j != size-1 && j != 0) massive[i][j] = massive[i][j+1] - 1;
        }
    }

    for(int i = size-1; i >= 0; i--){
        for(int j = size-1; j >=0; j--){
            if(i == size-1 && j%2 == 1 && j != size-1)massive[i][j] = massive[i][j+1] - 2 - 4*(size-1-j/2);
            else if(i == size-1 && j%2 == 0 && j != size-1 && j != 0) massive[i][j] = massive[i][j+1] - 1;
        }
    }
    
    //input unfo
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(massive[i][j] < 10) std::cout << "  " << massive[i][j] << " "; 
            else if(massive[i][j] < 100) std::cout << " " << massive[i][j] << " ";
            else std::cout << massive[i][j] << " ";
        }
        std::cout << std::endl;
    }
}