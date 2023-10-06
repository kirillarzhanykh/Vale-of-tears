#define EPS 0.000001

int solver(int n, double* A, double* b, double* x){
    double buf, buf2;
    int num = 0;
    for(int i = 0; i < n; i++){
        buf = 0;
        num = i;
        //Выбираем строку с максимальным первым элементом
        for(int j = i; j < n ; j++){
            if(A[j * n + i] * A[j * n + i] > buf){
                buf = A[j * n + i] * A[j * n + i];
                num = j; 
            }
        }

        //Переносим эту строку наверх
        for(int j = i; j < n ; j++){
            buf = A[num * n + j];
            A[num * n + j] = A[i * n + j];
            A[i * n + j] = buf;
        }
        buf = b[num];
        b[num] = b[i];
        b[i] = buf;

        //Вычитаем строку из нижеследующих
        buf = A[i * n + i];
        for(int j = i + 1; j < n; j++){
            buf2 = A[j * n + i] / buf;
            for(int k = i; k < n; k++){
                A[j* n + k] -= A[i * n + k] * buf2;
            }
            b[j] -= b[i] * buf2;
        }
    }

    for(int i = n - 1; i >= 0; i--){
        x[i] = b[i];
        for(int j = n - 1; j > i; j--){
            x[i] -= x[j] * A[i * n + j];
        }
        if(A[i * n + i] < EPS && A[i * n + i] > -EPS) return -1;
        x[i] = x[i] / A[i * n + i];
    }

    return 0;
}