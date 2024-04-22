
/* Приближение функции, заданной в ромбе, 
конечными элементами степени 2 методом наименьших квадратов

a*x^2 + b*xy + c*y^2 + d*x + e*y + f

*/

#include <fstream>
#include <iostream>
#include <cmath>
#include "solver_H.h"

double function(double x, double y);

int interpolation(int n, double** coeff, double x, double y);

void triangle_interpol(double x1, double y1, double x2, double y2, double x3, double y3, double* coeff);
    

int main(void){
    int n = 1;
    std::cin >> n;
    if(n < 1) return -1;
    double** polynomials;
    polynomials = new double *[n]; 
    for(int i = 0; i < 4 * n; i++){
        polynomials[i] = new double [6]; 
    }

    interpolation(n, polynomials, 1, 1);


    for(int k = 0; k < 4 * n; k++){
        delete[] polynomials[k];
    }
    delete[] polynomials;
    return 0;
}

double function(double x, double y){
    return x*y;
}

int interpolation(int n, double** coeff, double x, double y){
    for(int i = 0; i < 4 * n; i++){
        for(int j = 0; j < 4 * n; j++){
           

            triangle_interpol(x1, y1, x2, y2, x3, y3, coeff[k]){
     
        }
    }
    return 0;
}

void triangle_interpol(double x1, double y1, double x2, double y2, double x3, double y3, double* coeff){
    for(int j = 0; j < 6; j++){
        coeff[j] = 0;         
    }

    double new_x1 = (10*x1 + x2 + x3)/12;
    double new_y1 = (10*y1 + y2 + y3)/12;
    double new_x2 = (10*x2 + x1 + x3)/12;
    double new_y2 = (10*y2 + y1 + y3)/12;
    double new_x3 = (10*x3 + x2 + x1)/12;
    double new_y3 = (10*y3 + y2 + y1)/12;
    double new_x4 = (new_x2 + new_x3)/2;
    double new_y4 = (new_y2 + new_y3)/2;
    double new_x5 = (new_x1 + new_x3)/2;
    double new_y5 = (new_y1 + new_y3)/2;
    double new_x6 = (new_x1 + new_x2)/2;
    double new_y6 = (new_y1 + new_y2)/2;

    double buf;
    double[3] buf1;
    double[3] buf2;

    psi(new_x3, new_y3, new_x2, new_y2, new_x1, new_y1, buf1);
    psi(new_x5, new_y5, new_x6, new_y6, new_x1, new_y1, buf2);
    buf = function(new_x1, new_y1);
    coeff[1] += buf*(buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[2] + buf1[2]*buf2[1]);
    coeff[3] += buf*(buf1[2]*buf2[2]);
    coeff[4] += buf*(buf1[1]*buf2[3] + buf1[3]*buf2[1]);
    coeff[5] += buf*(buf1[3]*buf2[2] + buf1[2]*buf2[3]);
    coeff[6] += buf*(buf1[3]*buf2[3]);

    psi(new_x3, new_y3, new_x1, new_y1, new_x2, new_y2, buf1);
    psi(new_x4, new_y4, new_x6, new_y6, new_x2, new_y2, buf2);
    buf = function(new_x2, new_y2);
    coeff[1] += buf*(buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[2] + buf1[2]*buf2[1]);
    coeff[3] += buf*(buf1[2]*buf2[2]);
    coeff[4] += buf*(buf1[1]*buf2[3] + buf1[3]*buf2[1]);
    coeff[5] += buf*(buf1[3]*buf2[2] + buf1[2]*buf2[3]);
    coeff[6] += buf*(buf1[3]*buf2[3]);

    psi(new_x1, new_y1, new_x2, new_y2, new_x3, new_y3, buf1);
    psi(new_x5, new_y5, new_x4, new_y4, new_x3, new_y3, buf2);
    buf = function(new_x3, new_y3);
    coeff[1] += buf*(buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[2] + buf1[2]*buf2[1]);
    coeff[3] += buf*(buf1[2]*buf2[2]);
    coeff[4] += buf*(buf1[1]*buf2[3] + buf1[3]*buf2[1]);
    coeff[5] += buf*(buf1[3]*buf2[2] + buf1[2]*buf2[3]);
    coeff[6] += buf*(buf1[3]*buf2[3]);

    psi(new_x3, new_y3, new_x1, new_y1, new_x4, new_y4, buf1);
    psi(new_x2, new_y2, new_x1, new_y1, new_x4, new_y4, buf2);
    buf = function(new_x4, new_y4);
    coeff[1] += buf*(buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[2] + buf1[2]*buf2[1]);
    coeff[3] += buf*(buf1[2]*buf2[2]);
    coeff[4] += buf*(buf1[1]*buf2[3] + buf1[3]*buf2[1]);
    coeff[5] += buf*(buf1[3]*buf2[2] + buf1[2]*buf2[3]);
    coeff[6] += buf*(buf1[3]*buf2[3]);

    psi(new_x3, new_y3, new_x2, new_y2, new_x5, new_y5, buf1);
    psi(new_x2, new_y2, new_x1, new_y1, new_x5, new_y5, buf2);
    buf = function(new_x5, new_y5);
    coeff[1] += buf*(buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[2] + buf1[2]*buf2[1]);
    coeff[3] += buf*(buf1[2]*buf2[2]);
    coeff[4] += buf*(buf1[1]*buf2[3] + buf1[3]*buf2[1]);
    coeff[5] += buf*(buf1[3]*buf2[2] + buf1[2]*buf2[3]);
    coeff[6] += buf*(buf1[3]*buf2[3]);

    psi(new_x3, new_y3, new_x1, new_y1, new_x6, new_y6, buf1);
    psi(new_x2, new_y2, new_x3, new_y3, new_x6, new_y6, buf2);
    buf = function(new_x6, new_y6);
    coeff[1] += buf*(buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[2] + buf1[2]*buf2[1]);
    coeff[3] += buf*(buf1[2]*buf2[2]);
    coeff[4] += buf*(buf1[1]*buf2[3] + buf1[3]*buf2[1]);
    coeff[5] += buf*(buf1[3]*buf2[2] + buf1[2]*buf2[3]);
    coeff[6] += buf*(buf1[3]*buf2[3]);
}

void psi(double x1, double y1, double x2, double y2, double x0, double y0, double* coeff){ //в (x0, y0) единица
    coeff[1] = y2 - y1;
    coeff[2] = x1 - x2;
    coeff[3] = x1*(y1 - y2) + y1*(x2 - x1);
    double buf = x0 * coeff[1] + y0 * coeff[2] + coeff[3];
    coeff[1] /= buf;
    coeff[2] /= buf;
    coeff[3] /= buf;

    buf = x0 * coeff[1] + y0 * coeff[2] + coeff[3];
    std::cout << buf;
}
