#include "eigenvalues_QR.h"

int eigenvalues(int n, double* A, double* B, double* C, double* EigenValues, double eps){

    int flag = 1;
    double sum = 0.0; // s_k
    double aNorm = 0.0; // ||a_1ˆ(k-1)||
    double xNorm = 0.0; // ||xˆ(k)||
    double Uk = 0.0; // U(x)
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            B[i*n + j] = (i == j)*1.0;
        }
    }
    
    for(int k = 0; k < n; k++){
        
        sum = 0.0;
        
        for(int j = k + 1; j < n ;  j++  ){
            sum += A[j*n + k] * A[j*n + k];
        }
      
        aNorm = std::sqrt(A[k*n + k]*A[k*n + k] + sum);
        
        if(aNorm < 1e-100 ){
            return -1;
        }
        
        A[k*n + k] -= aNorm;
        
        xNorm = std::sqrt((A[k*n + k])*(A[k*n + k]) + sum);
        
        if (xNorm < 1e-100)
        {
            A[k * n + k] += aNorm;
            continue;
        }
        
        for(int j = k; j < n; j++){
            A[j*n + k] = 1.0 * A[j*n + k] / xNorm;
        }
        
        for(int i = k; i < n;i++){
            Uk = 0.0;
            for(int j = k; j < n; j++){
                Uk += A[j * n + k] * A[j * n + i];
            }
            for(int j = k; j < n; j++){
                A[j * n + i] -= 2 * Uk * A[j * n + k];
            }
        }
        
        for (int i = 0; i < n; i++ )
        {
            Uk = 0.0;
            for (int j = k; j < n; j++){
                Uk += A[j * n + k] * B[j * n + i];
            }
            for (int j = k; j < n; j++){
                B[j * n + i] -=  2 * Uk * A[j * n + k];
            }
                
        }
        
        A[k * n + k] = aNorm;
    }
    
    //double x, y, cos, sin;

    for(int m = 0; m < 100; m++){
        /*
        for(int i = 0; i < n; i++){
            for(int j = i; j < n; j++){
                x = A[i * n + i];
                y = A[j * n + i];
                if( x * x + y * y > 0 ){
                    cos = x / std::sqrt(x * x + y * y);
                    sin = y / std::sqrt(x * x + y * y);
                    for(int k = 0; k < n; k++){
                        A[]
                    }
                }
            }
        }


        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                A[i * n + j] = 0;
                for(int k = 0; k < n; k++){
                    A[i * n + j] += B[i * n + k] * C[k * n + j];
                }
            }
        }
        */
        flag = 1;

        for(int i = 0; i < n; i++){
            if(fabs(EigenValues[i] - A[i * n + i]) > eps) flag = 0;
        }

        if(flag == 1) return 0;
        
        for(int i = 0; i < n; i++){
            EigenValues[i] = A[i * n + i];
        }
    }
    return 0;
}