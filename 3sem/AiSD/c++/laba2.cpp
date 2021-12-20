#include "mergesort.h"
#include "matrix.h"
#include <iostream>

int main(){
    std::vector<Matrix<int>> matrixs;
    int counter = 0;
    std::cin >> counter;
    for(int t_number = 0; t_number < counter; t_number++){
        int t_size = 0;
        std::cin >> t_size;
        std::vector<int> data(t_size*t_size);
        for(int i = 0; i < t_size*t_size; i++){
            std::cin >> data[i];
        }

        Matrix<int> matrix(t_number, t_size);
        matrix.fill(data);
        matrixs.push_back(matrix);
    }

    mergesort(matrixs, true);
    for(int i = 0; i < counter; i++) std::cout << matrixs[i].get_number() << ' ';
    std::cout << std::endl;
    return 0;
}