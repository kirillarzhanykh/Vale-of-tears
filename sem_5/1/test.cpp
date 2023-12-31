#include <iostream>
#include <cstring>
#include "matrix_creator.h"
#include "solver_H.h"
#include <random>
#include <time.h>

int matrix_writer(int a, int b, int m, double* matrix);

int right_side_creator(int n, double* matrix, double* right_side);

double norm(int n, double* vector);

double relative_norm(int n, double* first_vector, double* second_vector);

void copy_filler(int n, double* from, double* to);

int main(int argc, char* argv[]){
   
    if (argc < 4){
        std::cout << "дурак" << std::endl;
        return 0;
    } 
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int k = atoi(argv[3]);
    char filename[20];
    if(argc == 5){
        strcpy(filename, argv[4]);
    }

    double* M;
    M = new double[n*n];
    if(matrix_creator(n, k, filename, M) != 0){ 
        delete[] M;
        return 0;
    }
    double* M_copy;
    M_copy = new double[n*n];
    copy_filler(n*n, M, M_copy);

    double* b;
    b = new double[n];
    right_side_creator(n, M, b);
    double* b_copy;
    b_copy = new double[n];
    copy_filler(n, b, b_copy);

    double* Res_Real;
    Res_Real = new double[n];
    for(int i = 0; i < n; i++){
        Res_Real[i] = 0;
        Res_Real[i] += ((i + 1) % 2);
    }

    double* Res;
    Res = new double[n];
    double* Raznost;
    Raznost = new double[n];

    clock_t start = clock();
    if(solver(n, M_copy, b_copy, Res) == -1){
        std::cout << "Матрица вырождена!" << std::endl;
    } else {
        clock_t end = clock();
        double seconds =  static_cast<double>(end - start) / CLOCKS_PER_SEC;
        for(int i = 0; i < n; i++){
            Raznost[i] = Res[i] - Res_Real[i];
        }
        for(int i = 0; i < n; i++){
            b_copy[i] = 0;
            for(int j = 0; j < n; j++){
                b_copy[i] += Res[j] * M[i * n + j];
            }
        }
        matrix_writer(n, n, m, M);
        matrix_writer(n, 1, m, Res);
        std::cout << "\n";
        std::cout << "Норма невязки (относительная): " << relative_norm(n, b_copy, b) << std::endl;
        std::cout << "\n";
	    std::cout << "Норма погрешности: " << norm(n, Raznost) << std::endl;
        std::cout << "\n";
        std::cout << "Время решения системы: " << seconds << " сек" << std::endl;
    }
	delete[] Raznost;
    delete[] M;
    delete[] M_copy;
    delete[] b;
    delete[] b_copy;
    delete[] Res_Real;
    delete[] Res;
    return 0;
}


int matrix_writer(int a, int b, int m, double* matrix){
    for(int i = 0; i < std::min(m, a); i++){
        std::cout << "\n";
        for(int j = 0; j < std::min(m, b); j++){
            std::cout.precision(3);
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
            right_side[i] += matrix[i * n + j];
        }
    }
    return 0;
}

double norm(int n, double* vector){
    double Sq = 0;
    for(int i = 0; i < n; i++){
        Sq += pow(vector[i], 2);
    }
    return sqrt(Sq);
}

double relative_norm(int n, double* first_vector, double* second_vector){
    double* difference;
    double Res;
    difference = new double[n];

    for(int i = 0; i < n; i++){
        difference[i] = first_vector[i] - second_vector[i];
    }

    Res = norm(n, difference) / norm(n, second_vector);
    delete[] difference;
    return Res;
}

void copy_filler(int n, double* from, double* to){
    for(int i = 0; i < n; i++){
        to[i] = from[i];
    }    
}
