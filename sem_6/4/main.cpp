
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
    
void psi(double x1, double y1, double x2, double y2, double x0, double y0, double* coeff);

int main(void){
    int n = 1;
    std::cin >> n;
    if(n < 1) return -1;
    double** polynomials;
    polynomials = new double *[2 * n * n]; 
    for(int i = 0; i < 2 * n * n; i++){
        polynomials[i] = new double [6]; 
    }

    double x = 1;
    double y = 1;

    interpolation(n, polynomials, x, y);

    std::ofstream scriptFile("plot_script.gp");
    scriptFile << "set terminal pngcairo enhanced color size 1000,1000\n";
    scriptFile << "set output 'PCA.png'\n";
    scriptFile << "f(x, y) =  x*y*x\n";
    int k;
    double d_x = 2 * x / n;
    double d_y = 2 * y / n;
    double x1, y1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2 * n; j++){                                           
            k = i * 2 * n + j;
            if(j%2 == 0){     
                x1 = -x + d_x * (j/2);       
                y1 = y - d_y * i; 
                scriptFile << "p_" << k << "(x, y) =  ("<< x1 <<" < x && x < "<< x1 + d_x <<" && " << y1 - d_y <<" < y && y < "<< y1 <<") ? " << polynomials[k][0] << "*(x**2) + " << polynomials[k][1] << "*(x*y) + " << polynomials[k][2] << "*(y**2) + " << polynomials[k][3] << "*(x) + " << polynomials[k][4] << "*(y) + " << polynomials[k][5] << ": 1/0\n";
            }else{    
                x1 = -x + d_x * ((j/2) + 1);  
                y1 = y - d_y * i;                     
                scriptFile << "p_" << k << "(x, y) =  ("<< x1 <<" < x && x < "<< x1 + d_x <<" && " << y1 - d_y <<" < y && y < "<< y1 <<") ? " << polynomials[k][0] << "*(x**2) + " << polynomials[k][1] << "*(x*y) + " << polynomials[k][2] << "*(y**2) + " << polynomials[k][3] << "*(x) + " << polynomials[k][4] << "*(y) + " << polynomials[k][5] << ": 1/0\n";
            }
            
        }
    }

    scriptFile << "set xlabel 'x'\n";
    scriptFile << "set ylabel 'y'\n";
    scriptFile << "set zlabel 'z'\n";
    scriptFile << "set xrange[-" << x << ": " << x << "]\n";
    scriptFile << "set yrange[-" << y << ": " << y << "]\n";
    scriptFile << "splot f(x, y) lc rgb 'green' ";

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2 * n; j++){                                           
            k = i * 2 * n + j;
            scriptFile << ", p_" << k << "(x, y) lc rgb 'red' ";
        }
    }
    scriptFile.close();

    system("gnuplot plot_script.gp");


    for(int i = 0; i < 2 * n * n; i++){
        delete[] polynomials[i];
    }
    delete[] polynomials;
    return 0;
}

double function(double x, double y){
    return x*y*x;
}

int interpolation(int n, double** coeff, double x, double y){
    double d_x = 2 * x / n;
    double d_y = 2 * y / n;
    double x1, x2, x3, y1, y2, y3, new_x1, new_x2, new_x3, new_y1, new_y2, new_y3;
    int k;
            
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2 * n; j++){
                                                       
            if(j%2 == 0){                         //                    ___
                x1 = -x + d_x * (j/2);            //  типа треугольник  | /
                y1 = y - d_y * i;                 //                    |/
                x2 = x1 + d_x;
                y2 = y1;
                x3 = x1;
                y3 = y1 - d_y;
            }else{                         //                       /|
                x1 = -x + d_x * ((j/2) + 1);      //  типа треугольник    /_|
                y1 = y - d_y * i;
                x2 = x1;
                y2 = y1 - d_y;
                x3 = x1 - d_x;
                y3 = y1 - d_y;
            }
            
            new_x1 = (10*x1 + x2 + x3)/12;
            new_y1 = (10*y1 + y2 + y3)/12;
            new_x2 = (10*x2 + x1 + x3)/12;
            new_y2 = (10*y2 + y1 + y3)/12;
            new_x3 = (10*x3 + x2 + x1)/12;
            new_y3 = (10*y3 + y2 + y1)/12;

            k = i * 2 * n + j;
            triangle_interpol(new_x1, new_y1, new_x2, new_y2, new_x3, new_y3, coeff[k]);
        }
     
    }
    return 0;
}

void triangle_interpol(double x1, double y1, double x2, double y2, double x3, double y3, double* coeff){
    for(int j = 0; j < 6; j++){
        coeff[j] = 0;         
    }

    double x4 = (x2 + x3)/2;
    double y4 = (y2 + y3)/2;
    double x5 = (x1 + x3)/2;
    double y5 = (y1 + y3)/2;
    double x6 = (x1 + x2)/2;
    double y6 = (y1 + y2)/2;

    double buf;
    double buf1[3];
    double buf2[3];

    psi(x3, y3, x2, y2, x1, y1, buf1);
    psi(x5, y5, x6, y6, x1, y1, buf2);
    buf = function(x1, y1);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[5] += buf*(buf1[2]*buf2[2]);

    psi(x3, y3, x1, y1, x2, y2, buf1);
    psi(x4, y4, x6, y6, x2, y2, buf2);
    buf = function(x2, y2);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[5] += buf*(buf1[2]*buf2[2]);

    psi(x1, y1, x2, y2, x3, y3, buf1);
    psi(x5, y5, x4, y4, x3, y3, buf2);
    buf = function(x3, y3);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[5] += buf*(buf1[2]*buf2[2]);

    psi(x3, y3, x1, y1, x4, y4, buf1);
    psi(x2, y2, x1, y1, x4, y4, buf2);
    buf = function(x4, y4);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[5] += buf*(buf1[2]*buf2[2]);

    psi(x3, y3, x2, y2, x5, y5, buf1);
    psi(x2, y2, x1, y1, x5, y5, buf2);
    buf = function(x5, y5);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[5] += buf*(buf1[2]*buf2[2]);

    psi(x3, y3, x1, y1, x6, y6, buf1);
    psi(x2, y2, x3, y3, x6, y6, buf2);
    buf = function(x6, y6);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[5] += buf*(buf1[2]*buf2[2]);
}

void psi(double x1, double y1, double x2, double y2, double x0, double y0, double* coeff){ //в (x0, y0) единица
    coeff[0] = y2 - y1;
    coeff[1] = x1 - x2;
    coeff[2] = x1*(y1 - y2) + y1*(x2 - x1);
    double buf = x0 * coeff[0] + y0 * coeff[1] + coeff[2];
    coeff[0] /= buf;
    coeff[1] /= buf;
    coeff[2] /= buf;

    buf = x0 * coeff[0] + y0 * coeff[1] + coeff[2];
}
