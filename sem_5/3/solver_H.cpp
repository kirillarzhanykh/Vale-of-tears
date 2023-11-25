#include "solver_H.h"
#include <iostream>
#include <pthread.h>
#include <cmath>
#define EPS 10e-17

void synchronize(int total_threads){
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t condvar_in = PTHREAD_COND_INITIALIZER;
	static pthread_cond_t condvar_out = PTHREAD_COND_INITIALIZER;
	static int threads_in = 0;
	static int threads_out = 0;

	pthread_mutex_lock(&mutex);

	threads_in++;
	if (threads_in >= total_threads){
		threads_out = 0;
		pthread_cond_broadcast(&condvar_in);
	} else {
		while (threads_in < total_threads){
			pthread_cond_wait(&condvar_in,&mutex);
		}
	}
	threads_out++;
	if (threads_out >= total_threads){
		threads_in = 0;
		pthread_cond_broadcast(&condvar_out);
	} else {
		while (threads_out < total_threads){
			pthread_cond_wait(&condvar_out,&mutex);
		}
	}
	pthread_mutex_unlock(&mutex);
}

int solver(int n, int cur_thread, int n_threads, double* A, double* b, double* x){
    long double buf, buf2;
    int num = 0;
	int chunk;
    // Нормируем матрицу
	if(cur_thread == 0){
		buf = 0;
		for(int i = 0; i < n; i++){
			buf2 = 0;
			for(int j = 0; j < n; j++){
				if(fabs(A[i * n + j]) > buf2) buf2 = fabs(A[i * n + j]);
			}
			buf += buf2;
		}
		if (buf <= 0) return -1;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				A[i * n + j] = A[i * n + j] / buf;
			}
		}
		for(int i = 0; i < n; i++){
			b[i] = b[i] / buf;
		}
	}

	synchronize(n_threads);


	for(int i = 0; i < n; i++){
		std::cout << cur_thread;
		if(cur_thread == 0){
			buf = 0;
			num = i;
			//Выбираем строку с максимальным первым элементом
			for(int j = i; j < n ; j++){
				if(A[j * n + i] * A[j * n + i] > buf){
					buf = A[j * n + i] * A[j * n + i];
					num = j; 
				}
			}
			if(A[num * n + i] < EPS && A[num * n + i] > -EPS) return -1;

			//Переносим эту строку наверх
			for(int j = i; j < n ; j++){
				buf = A[num * n + j];
				A[num * n + j] = A[i * n + j];
				A[i * n + j] = buf;
			}
			buf = b[num];
			b[num] = b[i];
			b[i] = buf;
		}
		synchronize(n_threads);
		
		//Вычитаем строку из нижеследующих
		if((n - i) % n_threads == 0){
			chunk = (n - i) / n_threads;
		} else {
			chunk = (n - i) / n_threads + 1;
		}
		if(cur_thread == n_threads - 1){
			buf = A[i * n + i];
			for(int j = i + 1; j < n; j++){
				buf2 = A[j * n + i] / buf;
				for(int k = i + chunk * cur_thread; k < n; k++){
					A[j* n + k] -= A[i * n + k] * buf2;
				}
				b[j] -= b[i] * buf2;  // разница только здесь 
			}
		} else {
			buf = A[i * n + i];
			for(int j = i + 1; j < n; j++){
				buf2 = A[j * n + i] / buf;
				for(int k = i + chunk * cur_thread ; k < i + chunk * (cur_thread + 1); k++){
					A[j* n + k] -= A[i * n + k] * buf2;
				}
			}
		}
		synchronize(n_threads);
	}
	
	if(cur_thread == 0){
		for(int i = n - 1; i >= 0; i--){
			x[i] = b[i];
			for(int j = n - 1; j > i; j--){
				x[i] -= x[j] * A[i * n + j];
			}
			x[i] = x[i] / A[i * n + i];
		}
	}

    return 0;
}