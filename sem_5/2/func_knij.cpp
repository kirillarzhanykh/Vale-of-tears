#include "func_knij.h"

double func(int k, int n, int i, int j){
    if(k == 1){
        return n - fmax(i, j);
    }

    if(k == 2){
        if(i == j) return 2;
        if(i == j - 1 || i == j + 1) return -1;
        return 0;
    }

    if(k == 3){
        if(i == n - 1) return j + 1;
        if(j == n - 1) return i + 1;
        if(j == i) return 1;
        return 0;
    }

    if(k == 4){
        return 1.0 / (i + j + 1);
    }

    return 0;    
}