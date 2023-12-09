#include "multiplier.h"
#include <iostream>
#include <pthread.h>
#include <cmath>
#define EPS 10e-17

int multiplier(int n, int cur_thread, int n_threads, double* A, double* b, double* x){

	int chunk;

    if(n % n_threads == 0){
        chunk = n / n_threads;
    } else {
        chunk = n / n_threads + 1;
    }

    for(int i = chunk * cur_thread; i < std::min(chunk * (cur_thread + 1), n); i++){
        b[i] = 0;
        for(int j = 0; j < n; j++){
            b[i] += x[j] * A[i * n + j];
        }
    }

    return 0;
}