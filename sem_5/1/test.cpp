#include <iostream>
#include <cstring>
#include "matrix_creator.hpp"
#include "solver_H.hpp"
#include <random>
#include <time.h>

int matrix_writer(int a, int b, int m, double* matrix);

int right_side_creator(int n, double* matrix, double* right_side);

int main(int argc, char* argv[]){
   
    if (argc < 4){
        std::cout << "дурак" << std::endl;
    } 
    int n = argv[1][0] - '0';
    int m = argv[2][0] - '0';
    int k = argv[3][0] - '0';
    char filename[20];
    if(argc == 5){
        strcpy(filename, argv[4]);
    }

    double* M;
    M = new double[n*n];
    matrix_creator(n, k, filename, M);

    double* b;
    b = new double[n];
    right_side_creator(n, M, b);

    double* Res;
    Res = new double[n];

    solver(n, M, b, Res);

    matrix_writer(n, n, m, M);
    matrix_writer(n, 1, m, b);
    delete[] M;
    delete[] b;
    delete[] Res;
    return 0;
}


int matrix_writer(int a, int b, int m, double* matrix){
    for(int i = 0; i < std::min(m, a); i++){
        std::cout << "\n";
        for(int j = 0; j < std::min(m, b); j++){
            std::cout << matrix[i * b + j] << "   ";
        }
        std::cout << "\n";   
    } 
    return 0;
}

int right_side_creator(int n, double* matrix, double* right_side){
    for(int i = 0; i < n; i++){
        right_side[i] = 0;
        for(int j = 0; j < n; j += 2){
            right_side[i] += matrix[i * n + j + 1];
        }
    }
    return 0;
}