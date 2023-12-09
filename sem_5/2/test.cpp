#include <iostream>
#include <cstring>
#include "matrix_creator.h"
#include "eigenvalues_QR.h"
#include <random>
#include <time.h>

int matrix_writer(int a, int b, int m, double* matrix);

void copy_filler(int n, double* from, double* to);

int main(int argc, char* argv[]){
   
    if (argc < 5){
        std::cout << "дурак" << std::endl;
        return 0;
    } 
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    double eps = atof(argv[3]);
    int k = atoi(argv[4]);
    char filename[20];
    if(argc == 6){
        strcpy(filename, argv[5]);
    }

    if(m > n || m < 0 || n < 0 || eps < 1e-20){
        std::cout << "подумай ещё" << std::endl;
        return 0;
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

    double* Res;
    Res = new double[n + 2];

    double* Mem1;
    Mem1 = new double[n*n + 1];
	for(int i = 0; i < n * n; i++){
		Mem1[i] = 0;
	}
	for(int i = 0; i < n; i++){
		Res[i] = 0;
	}

    int flag;
    clock_t start = clock();
    flag = eigenvalues(n, M_copy, Mem1, Res, eps);
    clock_t end = clock();
    if(flag == -1){    //Да, этот случай невозможен, ещё вопросы?
        std::cout << "Ошибка!" << std::endl; 
    } else {
        double seconds =  static_cast<double>(end - start) / CLOCKS_PER_SEC;

        double trace_M = 0;
        for(int i = 0; i < n; i++){
            trace_M += M[i * n + i];
        }
        double sum1 = 0;
        for(int i = 0; i < n; i++){
            sum1 += Res[i];
        }

        double length_M = 0;
        for(int i = 0; i < n*n; i++){
            length_M += M[i] * M[i];
        }
        double sum2 = 0;
        for(int i = 0; i < n; i++){
            sum2 += Res[i] * Res[i];
        }
    
        std::cout << "\n" << "Данная матрица: " << std::endl;
        matrix_writer(n, n, m, M);
        std::cout << "\n" << "Матрица после преобразований: " << std::endl;
        matrix_writer(n, n, m, M_copy);
        std::cout.precision(3);
        if(flag > 2){
            //std::cout << "\n" << "Больше двух невещественных собственных значений,\n или недостаточная точность метода (алгоритм не сошёлся)!" << std::endl;
            std::cout << "\n" << "Вектор из чисел на диагонали: " << std::endl;
            for(int i = 0; i < m; i++){
                std::cout << "\n" << Res[i] << "\n";
            }
        } else if(fabs(Res[n]) < 1e-20){
            std::cout << "\n" << "Вектор собственных чисел (вещественных): " << std::endl;
            matrix_writer(n, 1, m, Res);
        } else {
            std::cout << "\n" << "Вектор собственных чисел (не только вещественных): " << std::endl;
            std::cout << "\n" << Res[0] << " + " << Res[n] << " * i" << std::endl;
            std::cout << "\n" << Res[0] << " - " << Res[n] << " * i" << std::endl;

            std::cout << "\n";
            for(int j = 2; j < n; j++){
                std::cout << Res[j];
            }
            std::cout << "\n";   
            sum2 -= Res[n] * Res[n];
            sum2 -= Res[n + 1] * Res[n + 1];
        }
        std::cout << "\n" << "Невязка в первом инварианте: " << fabs(trace_M - sum1) << std::endl;
        std::cout << "\n" << "Невязка во втором инварианте: " << fabs(length_M - sum2) << std::endl;
        std::cout << "\n" << "Время поиска собственных значений: " << seconds << " сек" << std::endl;
    }
    delete[] M;
    delete[] M_copy;
    delete[] Mem1;
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

void copy_filler(int n, double* from, double* to){
    for(int i = 0; i < n; i++){
        to[i] = from[i];
    }    
}
