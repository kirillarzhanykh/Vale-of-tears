#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

int matrix_reader(int n, double* matrix, char* filename);

int matrix_creator(int n, int k, char* filename, double* matrix){
    if(k == 0){
        if(matrix_reader(n, matrix, filename) != 0){
            std::cout << "Ошибка чтения матрицы из файла!" << std::endl;
        }
    }
    
    if(k == 1){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                matrix[i * n + j] = n - std::max(i, j);
            }
        }
    }

    if(k == 2){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                matrix[i * n + j] = std::max(i + 1, j + 1);
            }
        }
    }

    if(k == 3){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                matrix[i * n + j] = abs(i - j);
            }
        }
    }

    if(k == 4){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                matrix[i * n + j] = 1.0 / ( i + j + 3);
            }
        }
    }
    return 0;
}

int matrix_reader(int n, double* matrix, char* filename){
    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input >> matrix[i * n + j];
            if(input.eof()) return -1;
        }
    }

    input.close();
    return 0;
}
