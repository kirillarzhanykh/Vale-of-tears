#include "eigenvalues_QR.h"
#include <iostream>

int eigenvalues(int n, double* A, double* B, double* EigenValues, double eps){
    
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
    double x, y, buf, shift;

    //В этом блоке B используется для хранения разложения

    for(int m = 0; m < 10000; m++){

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


        // Подготовительная часть (строим единичную матрицу, зануляем псевдонули)
        
        for(int i = 0; i < n_Var; i++){
            for(int j = 0; j < n_Var; j++){
                if(fabs(A[i * n + j]) < 1e-20) A[i * n + j] = 0;
                if(i > j + 1) A[i * n + j] = 0;
            }
        }
        
        //Сдвиг

        shift = A[(n_Var - 1) * n + (n_Var - 1)] * 0;

        for(int i = 0; i < n_Var; i++){
            A[i * n + i] -= shift;
        }
    
        for(int i = 0; i < n_Var - 1; i++){
            int j = i + 1;
            x = A[i * n + i];
            y = A[j * n + i];
            if( x * x + y * y > 0 ){
                B[2 * i] = x / std::sqrt(x * x + y * y); //cos
                B[2 * i + 1] = - y / std::sqrt(x * x + y * y); //sin
                if(fabs(B[2 * i]) < 1e-20) B[2 * i] = 0;
                if(fabs(B[2 * i + 1] ) < 1e-20) B[2 * i + 1] = 0;
                for(int k = i + 1; k < n_Var; k++){
                    buf = A[i * n + k];
                  
                    A[i * n + k] = buf * B[2 * i] - A[j * n + k] * B[2 * i + 1];
                    A[j * n + k] = buf * B[2 * i + 1] + A[j * n + k] * B[2 * i];
                    
                }
                A[i * n + i] = std::sqrt(x * x + y * y);
                A[j * n + i] = 0;

            }
            
        }

     
        for(int i = 0; i < n_Var - 1; i++){
            for(int j = 0; j < i + 2; j++){
                x = A[j * n + i];
                y = A[j * n + i + 1];
                if(fabs(x) < 1e-20) x = 0;
                if(fabs(y) < 1e-20) y = 0;
                A[j * n + i] = x * B[2 * i] - y * B[2 * i + 1];
                A[j * n + i + 1] = x * B[2 * i + 1] + y * B[2 * i];
            }
        }

        //Сдвиг обратный

        for(int i = 0; i < n_Var; i++){
            A[i * n + i] += shift;
        }

        if(n_Var == 1) return 0;
        if(n_Var == 2){
            double a11 = A[0];
            double a12 = A[1];
            double a21 = A[n];
            double a22 = A[n + 1];
            double b = - (a11 + a22); 
            double c = a11 * a22 - a21 * a12;
            double R_P = - b / 2;
            double Im_P = 0;
            if( 4 * c - b * b > 0 ){
                Im_P = std::sqrt(4 * c - b * b) / 2;
                EigenValues[0] = R_P;
                EigenValues[1] = R_P;
                EigenValues[n] = Im_P;
                EigenValues[n + 1] = - Im_P;
            }else{
                Im_P = std::sqrt(b * b - 4 * c) / 2;
                EigenValues[0] = R_P + Im_P;
                EigenValues[1] = R_P - Im_P;
                EigenValues[n] = 0;
                EigenValues[n + 1] = 0;
            }
            return 0;
        }
    }

    n_Var--;
    return n_Var;
}
