int eigenvalues(int n, double* A, double* EigenValues, double eps){
    for(int i = 0; i < n; i++){
        EigenValues[i] = A[i * n + i];
    }
    return 0;
}