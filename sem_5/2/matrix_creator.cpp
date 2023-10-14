#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "matrix_creator.h"
#include "func_knij.h"

int matrix_reader(int n, double* matrix, char* filename);

int matrix_creator(int n, int k, char* filename, double* matrix){
    if(k == 0){
        if(matrix_reader(n, matrix, filename) != 0){
            std::cout << "Ошибка чтения матрицы из файла!" << std::endl;
            return -1;
        }
        return 0;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i * n + j] = func(k, n, i, j);
        }
    }
    return 0;
}

int matrix_reader(int n, double* matrix, char* filename){
    std::ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        //std::cout << "Ошибка открытия файла!" << std::endl;
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
