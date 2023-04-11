#include <iostream>
#include <cmath>

int main(){
    std::cout << "Введите количество строк в матрице: ";
    int a = 0;
    std::cin >> a;

    std::cout << "Введите количество столбцов в матрице: ";
    int b = 0;
    std::cin >> b;

    int matrix[a][b];
    std::cout << "Введите элементы матрицы: " << std::endl;
    for(int i = 1; i <= a; i++){
        for(int j = 1; j <= b; j++){
            std::cout << "matrix[" << i << "][" << j << "] = ";
            std::cin >> matrix[i][j];
        }
    }

    int vector[b];
    std::cout << "Введите элементы вектора: " << std::endl;
    for(int i = 1; i <= b; i++){
        std::cout << "vector[" << i << "] = ";
        std::cin >> vector[i];
    }

    std::cout << "Записанная матрица: " << std::endl;
    for(int i = 1; i <= a; i++){
        for(int j = 1; j <= b; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Записанный вектор: " << std::endl;
    for(int i = 1; i <= b; i++){
        std::cout << vector[i] << "\n";
    }

    int result[a];
    for(int i = 1; i <= a; i++) result[i] = 0;
    std::cout << "Результат произведения: " << std::endl;
    for(int i = 1; i <= a; i++){
        for(int j = 1; j <= b; j++){
            result[i] += matrix[i][j]*vector[j];
        }
    }

    for(int i = 1; i <= a; i++){
        std::cout << result[i] << "\n";
    }

    return 0;
}