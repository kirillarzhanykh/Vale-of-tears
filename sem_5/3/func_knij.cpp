#include "func_knij.h"

double func(int k, int n, int i, int j){
    if(k == 1){
        return n - fmax(i, j);
    }

    if(k == 2){
	    if(i == 1000) return 0;
        return fmax(i + 1, j + 1);
    }

    if(k == 3){
        if (i == 1000) return 0;
        return abs(i - j);
    }

    if(k == 4){
        return 1.0 / (i + j + 1);
    }

    return 0;    
}
