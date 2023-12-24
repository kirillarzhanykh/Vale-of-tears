#include <iostream>
#include <cstring>
#include <cmath>
#include "matrix_creator.h"
#include "solver_H.h"
#include "multiplier.h"
#include <pthread.h>
#include <sys/time.h>

int matrix_writer(int a, int b, int m, double* matrix);

int right_side_creator(int n, double* matrix, double* right_side);

double norm(int n, double* vector);

double relative_norm(int n, double* first_vector, double* second_vector);

void copy_filler(int n, double* from, double* to);

void *solve(void *arg);

void *multiply(void *arg);

typedef struct
{
	int n;
    int cur_thread;
	int n_threads;
	double *M;
	double *b;
	double *Res;
    int *TERMINATOR;
} ARGS;

int flag = 0;
double sec, sec2;


int main(int argc, char* argv[]){
   
    if (argc < 4){
        std::cout << "дурак" << std::endl;
        return 0;
    } 
    int n = atoi(argv[1]);
    int p = atoi(argv[2]);
    int m = atoi(argv[3]);
    int s = atoi(argv[4]);
    char filename[20];
    if(argc == 6){
        strcpy(filename, argv[5]);
    }
    if(m > n){
        std::cout << "подумай ещё" << std::endl;
        return 0;
    }
    if(p < 1){
        std::cout << "подумай ещё" << std::endl;
        return 0;
    }

    double* M;
    M = new double[n*n];
    if(matrix_creator(n, s, filename, M) != 0){ 
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
    double* Res;
    Res = new double[n];
    double* Raznost;
    Raznost = new double[n];

    for(int i = 0; i < n; i++){
        Res_Real[i] = 0;
        Res_Real[i] += ((i + 1) % 2);
        Res[i] = 0;
        Raznost[i] = 0;
    }


    copy_filler(n*n, M, M_copy);
    copy_filler(n, b, b_copy);
    pthread_t* threads;
    threads = new pthread_t[p];
    ARGS* args;
    args = new ARGS[p];

    int TERMINATOR[1];
    TERMINATOR[0] = 0;

    for(int i = 0; i < p; i++){
        args[i].n = n;
        args[i].cur_thread = i;
        args[i].n_threads = p;
        args[i].M = M_copy;
        args[i].b = b_copy;
        args[i].Res = Res;
        args[i].TERMINATOR = TERMINATOR;
    }

    for(int i = 0; i < p; i++){
        if(pthread_create(threads + i, 0, solve, args + i) != 0){
            TERMINATOR[0] = -1;
            std::cout << "Не удалось создать поток!" << std::endl;
            for(int j = 0; j < (n * p * 100000); j++){
                flag = 0;
            }

            delete[] Raznost;
            delete[] M;
            delete[] M_copy;
            delete[] b;
            delete[] b_copy;
            delete[] Res_Real;
            delete[] Res;
            delete[] threads;
            delete[] args;
            return -1;
        }
    }
    for(int i = 0; i < p; i++){
        pthread_join(threads[i], 0);
    }

    //Невязка

    for(int i = 0; i < p; i++){
        args[i].n = n;
        args[i].cur_thread = i;
        args[i].n_threads = p;
        args[i].M = M;
        args[i].b = b_copy;
        args[i].Res = Res;
    }

    for(int i = 0; i < p; i++){
        if(pthread_create(threads + i, 0, multiply, args + i) != 0){
            std::cout << "Не удалось создать поток!" << std::endl;
            delete[] Raznost;
            delete[] M;
            delete[] M_copy;
            delete[] b;
            delete[] b_copy;
            delete[] Res_Real;
            delete[] Res;
            delete[] threads;
            delete[] args;
            return -1;
        }
    }
    for(int i = 0; i < p; i++){
        pthread_join(threads[i], 0);
    }

    if(flag == -1){
        std::cout << "Матрица вырождена!" << std::endl;
    } else {

        
        matrix_writer(n, n, m, M);
        matrix_writer(n, 1, m, Res);
        std::cout << "\n" <<  "Время решения системы: " << sec << std::endl;
        std::cout << "Время вычисления невязки: " << sec2 << std::endl;

        std::cout << "\n" << argv[0] << ": residual = " << relative_norm(n, b_copy, b) <<
        " elapsed = " << sec << " s = " << s << " n = " << n << " m = " << m <<
        " p = " << p << std::endl;
        
    }
    delete[] Raznost;
    delete[] M;
    delete[] M_copy;
    delete[] b;
    delete[] b_copy;
    delete[] Res_Real;
    delete[] Res;
    delete[] threads;
    delete[] args;
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

void *solve(void *arg){
    struct timeval start, end;
    ARGS *arg_ = static_cast<ARGS*> (arg);
    if(arg_->cur_thread == arg_->n_threads - 1) gettimeofday(&start, NULL);
    flag = solver(arg_->n, arg_->cur_thread, arg_->n_threads, arg_->M, arg_->b, arg_->Res, arg_->TERMINATOR);
    if(arg_->cur_thread == arg_->n_threads - 1) if(flag != -1) gettimeofday(&end, NULL);
    if(arg_->cur_thread == arg_->n_threads - 1)sec = (end.tv_sec - start.tv_sec);
    if(arg_->cur_thread == arg_->n_threads - 1)sec = ((sec * 1e6) + end.tv_usec) - (start.tv_usec);
    if(arg_->cur_thread == arg_->n_threads - 1)sec /= 1e6;
	return NULL;
}

void *multiply(void *arg){
    struct timeval start, end;
    gettimeofday(&start, NULL);
	ARGS *arg_ = static_cast<ARGS*> (arg);
    if(multiplier(arg_->n, arg_->cur_thread, arg_->n_threads, arg_->M, arg_->b, arg_->Res) == -1) flag = -1;
    gettimeofday(&end, NULL);
    sec2 = (end.tv_sec - start.tv_sec);
    sec2 = ((sec2 * 1e6) + end.tv_usec) - (start.tv_usec);
    sec2 /= 1e6;
	return NULL;
}
