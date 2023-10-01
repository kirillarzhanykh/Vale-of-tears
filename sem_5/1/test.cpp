#include <iostream>
#include <cstring>
#include <cmath>
#include <random>
#include <time.h>

int matrix_reader(int n, double* matrix, char* filename);

int main(int argc, char* argv[]){
   
    if (argc < 4){
        std::cout << "дурак" << std::endl;
    } 
    int n = argv[1][0] - '0';
    //int m = argv[2][0] - '0';
    int k = argv[3][0] - '0';
    char filename[20];
    if(argc == 5){
        strcpy(filename, argv[4]);
    }
    double* M;
    M = new double[n*n];

    if(k == 0){
        if(matrix_reader(n, M, filename) != 0){
            std::cout << "Ошибка чтения матрицы из файла!" << std::endl;
        }
    }
    if(k == 1){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                M[i * n + j] = n - std::max(i, j);
            }
        }
    }
    if(k == 2){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                M[i * n + j] = std::max(i + 1, j + 1);
            }
        }
    }
    if(k == 3){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                M[i * n + j] = abs(i - j);
            }
        }
    }
    if(k == 4){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                M[i * n + j] = 1 / ( i + j + 3);
            }
        }
    }



    return 0;
}

int matrix_reader(int n, double* matrix, char* filename){
    return 0;
}