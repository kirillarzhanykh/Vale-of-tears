
/* Построить линейную интерполяцию x^3 в линейном пространстве

< Cot(x)/2 + Sin(x)^2, Cot(x)/8, -x + 16x^2 / Pi, x >
через точки
{ -Pi/4, Pi/4, 3*Pi/2, Pi/2 }

*/

#include <iostream>
#include <cmath>
#include "solver_H.h"

int main(void){
    double x;
    double* points;
    points = new double[4];
    points[0] = - M_PI / 4;
    points[1] = M_PI / 4;
    points[2] = 3 * M_PI / 4;
    points[3] = M_PI / 2;

    double* Res;
    Res = new double[4];

    double* b;
    b = new double[4];
    for(int i = 0; i < 4; i++){
        x = points[i];
        b[i] = pow(x, 3);
    }

    double* A;
    A = new double[4*4];
    for(int i = 0; i < 4; i++){
        x = points[i];
        A[i * 4] = cos(x) / (2 * sin(x)) + pow(sin(x), 2);
        A[i * 4 + 1] = cos(x) / (8 * sin(x));
        A[i * 4 + 2] = -x + 16 * pow(x, 2) / M_PI;
        A[i * 4 + 3] = x;
        
    }

    if(solver(4, A, b, Res) == -1){
        std::cout << "Матрица вырождена!" << std::endl;
    }

    delete[] points;
    delete[] Res;
    delete[] b;
    delete[] A;
    return 0;
}