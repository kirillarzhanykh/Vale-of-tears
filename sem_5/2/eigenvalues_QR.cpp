#include "eigenvalues_QR.h"

int eigenvalues(int n, double* A, double* B, double* C, double* EigenValues, double eps){
    
    double sum; // s_k
    double aNorm; // ||a_1ˆ(k-1)||
    double xNorm; // ||xˆ(k)||
    double ScalProduct; // U(x)
    
    //В этом блоке B выступает хранилищем вектора отражения

    for(int k = 0; k < n - 2; k++){
        
        sum = 0;
        
        for(int j = k + 1; j < n; j++){
            sum += A[j * n + k] * A[j * n + k];
        }
      
        aNorm = std::sqrt(sum);
        
        if(aNorm < 1e-100 ){
            return -1;
        }
        
        xNorm = std::sqrt(sum - A[(k + 1)* n + k] * A[(k + 1)* n + k] + (A[(k + 1)* n + k] - aNorm) * (A[(k + 1)* n + k] - aNorm));
        
        if (xNorm < 1e-100)
        {
            return -1;
        }

        B[k] = 0;
        B[k + 1] = (A[(k + 1) * n + k] - aNorm) / xNorm;
        for(int j = k + 2; j < n; j++){
            B[j] = A[j * n + k] / xNorm;
        }
        
        //Умножение на матрицу отражения слева
        for(int i = k; i < n; i++){
            ScalProduct = 0;
            for(int j = k; j < n; j++){
                ScalProduct += B[j] * A[j * n + i];
            }
            for(int j = k; j < n; j++){
                A[j * n + i] -= 2 * ScalProduct * B[j];
            }
        }

        //Умножение на матрицу отражения справа
        
        for(int i = k; i < n; i++){
            ScalProduct = 0;
            for(int j = k; j < n; j++){
                ScalProduct += B[j] * A[i * n + j];
            }
            for(int j = k; j < n; j++){
                A[i * n + j] -= 2 * ScalProduct * B[j];
            }
        }
        
        
    }
    /*
    int flag = 1;
    double x, y, cos, sin, buf;

    for(int m = 0; m < 100; m++){

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                B[i * n + j] = (i == j);
            }
        }
    
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                x = A[i * n + i];
                y = A[j * n + i];
                if( x * x + y * y > 0 ){
                    cos = x / std::sqrt(x * x + y * y);
                    sin = y / std::sqrt(x * x + y * y);
                    for(int k = 0; k < n; k++){
                        buf = A[i * n + k];
                        A[i * n + k] = buf * cos - A[j * n + k] * sin;
                        A[j * n + k] = buf * sin + A[j * n + k] * cos;

                        buf = B[i * n + k];
                        B[i * n + k] = buf * cos - B[j * n + k] * sin;
                        B[j * n + k] = buf * sin + B[j * n + k] * cos; 
                    }
                }
            }
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                C[i * n + j] = A[i * n + j];
            }
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                A[i * n + j] = 0;
                for(int k = 0; k < n; k++){
                    A[i * n + j] += C[i * n + k] * B[k * n + j];
                }
            }
        }
    
        flag = 1;

        for(int i = 0; i < n - 1; i++){
            if(fabs(A[(i + 1) * n + i]) > eps) flag = 0;
        }

        if(flag == 1) return 0;
        
        for(int i = 0; i < n; i++){
            EigenValues[i] = A[i * n + i];
        }
    }
    */
    
    return 0;
}
