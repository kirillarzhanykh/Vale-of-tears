#include <iostream>
#include <cstring>
#include <cmath>
#include "matrix_creator.h"
#include "solver_H.h"
#include <pthread.h>
#include <sys/time.h>

int matrix_writer(int a, int b, int m, double* matrix);

int right_side_creator(int n, double* matrix, double* right_side);

double norm(int n, double* vector);

double relative_norm(int n, double* first_vector, double* second_vector);

void copy_filler(int n, double* from, double* to);

void *solve(void *arg);

typedef struct
{
	int n;
    int cur_thread;
	int n_threads;
	double *M;
	double *b;
	double *Res;
} ARGS;

int main(int argc, char* argv[]){
   
    if (argc < 4){
        std::cout << "дурак" << std::endl;
        return 0;
    } 
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int p = atoi(argv[3]);
    int s = atoi(argv[4]);
    char filename[20];
    if(argc == 6){
        strcpy(filename, argv[5]);
    }
    if(m > n){
        std::cout << "подумай ещё" << std::endl;
        return 0;
    }
    if(p > 4 || p < 1){
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
    for(int i = 0; i < n; i++){
        Res_Real[i] = 0;
        Res_Real[i] += ((i + 1) % 2);
    }

    double* Res;
    Res = new double[n];
    double* Raznost;
    Raznost = new double[n];

    double seconds;
    struct timeval start, end;

    copy_filler(n*n, M, M_copy);
    copy_filler(n, b, b_copy);
    pthread_t* threads;
    threads = new pthread_t[p];
    ARGS* args;
    args = new ARGS[p];

    if (!(M && b && Res && threads && args))
	{
		printf("Not enough memory!\n");
	}

    for(int i = 0; i < p; i++){
        args[i].n = n;
        args[i].cur_thread = i;
        args[i].n_threads = p;
        args[i].M = M_copy;
        args[i].b = b;
        args[i].Res = Res;
    }

    gettimeofday(&start, NULL);

    for(int i = 0; i < p; i++){
        pthread_create(threads + i, 0, solve, args + i);
    }
    for(int i = 0; i < p; i++){
        pthread_join(threads[i], 0);
    }

    gettimeofday(&end, NULL);

    if(1 == -1){
        std::cout << "Матрица вырождена!" << std::endl;
    } else {
        seconds = (end.tv_sec - start.tv_sec);
        seconds = ((seconds * 1e6) + end.tv_usec) - (start.tv_usec);
        seconds /= 1e6;
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

        std::cout << "\n" << argv[0] << ": residual = " << relative_norm(n, Res, Res_Real) <<
        " elapsed = " << seconds << " s = " << s << " n = " << n << " m = " << m <<
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

void *solve(void *arg)
{
	ARGS *arg_ = static_cast<ARGS*> (arg);
	solver(arg_->n, arg_->cur_thread, arg_->n_threads, arg_->M, arg_->b, arg_->Res);
	return NULL;
}