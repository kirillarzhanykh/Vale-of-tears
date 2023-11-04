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
            continue;
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
    
    int flag = 1;
    int n_Var = n;
    double x, y, cos, sin, buf;

    //В этом блоке B и C используются для хранения разложения

    for(int m = 0; m < 500; m++){

        for(int i = 0; i < n_Var; i++){
            for(int j = 0; j < n_Var; j++){
                B[i * n_Var + j] = (i == j);
            }
        }
    
        for(int i = 0; i < n_Var; i++){
            for(int j = i + 1; j < n_Var; j++){
                x = A[i * n_Var + i];
                y = A[j * n_Var + i];
                if( x * x + y * y > 0 ){
                    cos = x / std::sqrt(x * x + y * y);
                    sin = - y / std::sqrt(x * x + y * y);
                    for(int k = 0; k < n_Var; k++){
                        buf = A[i * n_Var + k];
                        A[i * n_Var + k] = buf * cos - A[j * n_Var + k] * sin;
                        A[j * n_Var + k] = buf * sin + A[j * n_Var + k] * cos;

                        buf = B[k * n_Var + i];
                        B[k * n_Var + i] = buf * cos - B[k * n_Var + j] * sin;
                        B[k * n_Var + j] = buf * sin + B[k * n_Var + j] * cos; 
                    }
                }
            }
        }
     
        for(int i = 0; i < n_Var; i++){
            for(int j = 0; j < n_Var; j++){
                C[i * n_Var + j] = A[i * n_Var + j];
            }
        }

        for(int i = 0; i < n_Var; i++){
            for(int j = 0; j < n_Var; j++){
                A[i * n_Var + j] = 0;
                for(int k = 0; k < n_Var; k++){
                    A[i * n_Var + j] += C[i * n_Var + k] * B[k * n_Var + j];
                }
            }
        }
        
        flag = 1;

        for(int i = 1; i < n_Var; i++){
            if(fabs(A[i * n_Var + i - 1]) > eps) flag = 0;
        }

        if(flag == 1){
            return 0;
        }

        for(int i = 0; i < n_Var; i++){
            EigenValues[i] = A[i * n_Var + i];
        }

        //if(fabs(A[(n_Var - 1) * (n_Var + 1) - 1]) < eps){
            //EigenValues[n_Var - 1] = A[(n_Var - 1) * n_Var + (n_Var - 1)];
            //n_Var--;
        //}
        
    }
    
    return 0;
}
