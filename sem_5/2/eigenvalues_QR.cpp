#include "eigenvalues_QR.h"

int eigenvalues(int n, double* A, double* B, double* C, double* EigenValues, double eps){
    
    double sum;
    double aNorm;
    double xNorm;
    double ScalProduct; 
    
    //В этом блоке B выступает хранилищем вектора отражения

    for(int k = 0; k < n - 2; k++){

        sum = 0;
        
        for(int j = k + 1; j < n; j++){
            sum += A[j * n + k] * A[j * n + k];
        }
      
        aNorm = std::sqrt(sum);
        
        if(aNorm < 1e-20){
            continue;
        }
        
        xNorm = std::sqrt(sum - A[(k + 1) * n + k] * A[(k + 1) * n + k] + (A[(k + 1) * n + k] - aNorm) * (A[(k + 1)* n + k] - aNorm));
        
        if (xNorm < 1e-20)
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
    double x, y, cos, sin, buf, shift;

    //В этом блоке B и C используются для хранения разложения

    for(int m = 0; m < 1000; m++){

        // Подготовительная часть (строим единичную матрицу, зануляем псевдонули)
        
        for(int i = 0; i < n_Var; i++){
            for(int j = 0; j < n_Var; j++){
                B[i * n + j] = (i == j);
                if(fabs(A[i * n + j]) < 1e-10) A[i * n + j] = 0;
                if(i > j + 1) A[i * n + j] = 0;
            }
        }
        

        //Сдвиг

        shift = A[(n_Var - 1) * n + (n_Var - 1)] * 0;

        for(int i = 0; i < n_Var; i++){
            A[i * n + i] -= shift;
        }
    
        for(int i = 0; i < n_Var - 1; i++){
            for(int j = i + 1; j < n_Var; j++){
                x = A[i * n + i];
                y = A[j * n + i];
                if( x * x + y * y > 0 ){
                    cos = x / std::sqrt(x * x + y * y);
                    sin = - y / std::sqrt(x * x + y * y);
                    if(fabs(sin) < 1e-10) sin = 0;
                    if(fabs(cos) < 1e-10) cos = 0;
                    for(int k = 0; k < n_Var; k++){
                        buf = A[i * n + k];
                        if(fabs(buf) < 1e-10) buf = 0;
                        A[i * n + k] = buf * cos - A[j * n + k] * sin;
                        A[j * n + k] = buf * sin + A[j * n + k] * cos;
    
                        buf = B[k * n + i];
                        if(fabs(buf) < 1e-10) buf = 0;
                        B[k * n + i] = buf * cos - B[k * n + j] * sin;
                        B[k * n + j] = buf * sin + B[k * n + j] * cos; 
                    }
                }
            }
        }
     
        for(int i = 0; i < n_Var; i++){
            for(int j = 0; j < n_Var; j++){
                C[i * n + j] = A[i * n + j];
            }
        }

        for(int i = 0; i < n_Var; i++){
            for(int j = std::fmax(0, i - 1); j < n_Var; j++){
                A[i * n + j] = 0;
                for(int k = i; k < n_Var; k++){
                    A[i * n + j] += C[i * n + k] * B[k * n + j];
                }
            }
        }

        //Сдвиг обратный

        for(int i = 0; i < n_Var; i++){
            A[i * n + i] += shift;
        }

        for(int i = 0; i < n_Var; i++){
            EigenValues[i] = A[i * n + i];
        }
        
        flag = 1;

        for(int i = 1; i < n_Var; i++){
            if(fabs(A[i * n + i - 1]) > eps) flag = 0;
        }

        if(flag == 1) return 0;

        //Исчерпывание

        if(fabs(A[(n_Var - 1) * n + (n_Var - 1) - 1]) < eps){
            EigenValues[n_Var - 1] = A[(n_Var - 1) * n + (n_Var - 1)];
            n_Var--;
        }
        if(n_Var <= 2) return n_Var;
    }
    return n_Var;
}
