
/* Приближение функции, заданной в ромбе, 
конечными элементами степени 2 методом наименьших квадратов

a*x^2 + b*xy + c*y^2 + d*x + e*y + f

*/

#include <fstream>
#include <iostream>
#include <cmath>
#include "solver_H.h"

double function(double x, double y);

int interpolation(int n, double** coeff, double** storage, double*** triangles_phi, double x, double y);

void triangle_interpol(double x1, double y1, double x2, double y2, double x3, double y3, double* coeff, double** phi);
    
void psi(double x1, double y1, double x2, double y2, double x0, double y0, double* coeff);

double integral(int pow_x, int pow_y, double b1_x, double b2_x, double b1_y, double b1_y_mult_x, double b2_y, double b2_y_mult_x);

double integral2(double* pol1, double* pol2, double b1_x, double b2_x, double b1_y, double b1_y_mult_x, double b2_y, double b2_y_mult_x);

int main(void){
    int n = 1;
    double x = 1;
    double y = 1;
    std::cin >> n >> x >> y;
    x = fabs(x);
    y = fabs(y);
    if(n < 1) return -1;
    double** polynomials1;
    double** polynomials2;
    double*** triangles_phi;
    polynomials1 = new double *[2 * n * n]; 
    polynomials2 = new double *[2 * n * n]; 
    triangles_phi = new double **[2 * n * n]; 
    for(int i = 0; i < 2 * n * n; i++){
        polynomials1[i] = new double [6]; 
        polynomials2[i] = new double [6];
        triangles_phi[i] = new double *[6]; 
        triangles_phi[i][0] = new double [6]; 
        triangles_phi[i][1] = new double [6]; 
        triangles_phi[i][2] = new double [6]; 
        triangles_phi[i][3] = new double [6]; 
        triangles_phi[i][4] = new double [6]; 
        triangles_phi[i][5] = new double [6]; 
        for(int j = 0; j < 6; j++){
            polynomials1[i][j] = 0; 
            polynomials2[i][j] = 0;   
            triangles_phi[i][0][j] = 0;  
            triangles_phi[i][1][j] = 0;  
            triangles_phi[i][2][j] = 0;  
            triangles_phi[i][3][j] = 0;  
            triangles_phi[i][4][j] = 0;  
            triangles_phi[i][5][j] = 0; 

        }
    }

    interpolation(n, polynomials1, polynomials2, triangles_phi, x, y);

    std::ofstream scriptFile("plot_script.gp");
    scriptFile << "set terminal pngcairo enhanced color size 1000,1000\n";
    scriptFile << "set output 'Triangulation.png'\n";
    scriptFile << "f(x, y) =  (x*x-y*y+exp(x)*sin(x)/(x**7)) \n";
    int k;
    double d_x = 2 * x / n;
    double d_y = 2 * y / n;
    double x1, y1;
    x1 = 0;
    y1 = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2 * n; j++){                                           
            k = i * 2 * n + j;
            if(j%2 == 0){     
                x1 = -x + d_x * (j/2);       
                y1 = y - d_y * i; 
                scriptFile << "p_" << k << "(x, y) =  ( (x/" << x << ") + (y/" << y << ") > 1 || (x/" << x << ") + (y/" << y << ") < -1 || -(x/" << x << ") + (y/" << y << ") > 1 || -(x/" << x << ") + (y/" << y << ") < -1) ? 1/0 : ("<< x1 <<" < x && x < "<< x1 + d_x << " && (" << y1 - d_y << " + " << d_y / d_x << "*(x - " << x1 << ")) < y && y < " << y1 << ") ? " << polynomials1[k][0] << "*(x**2) + " << polynomials1[k][1] << "*(x*y) + " << polynomials1[k][2] << "*(y**2) + " << polynomials1[k][3] << "*(x) + " << polynomials1[k][4] << "*(y) + " << polynomials1[k][5] << ": 1/0\n";
            }else{    
                x1 = -x + d_x * ((j/2) + 1);  
                y1 = y - d_y * i;                     
                scriptFile << "p_" << k << "(x, y) =  ( (x/" << x << ") + (y/" << y << ") > 1 || (x/" << x << ") + (y/" << y << ") < -1 || -(x/" << x << ") + (y/" << y << ") > 1 || -(x/" << x << ") + (y/" << y << ") < -1) ? 1/0 : ("<< x1 - d_x <<" < x && x < "<< x1 <<" && " << y1 - d_y << " < y && y < (" << y1 - d_y << " + " << d_y / d_x << "*(x - " << x1 - d_x << "))) ? " << polynomials1[k][0] << "*(x**2) + " << polynomials1[k][1] << "*(x*y) + " << polynomials1[k][2] << "*(y**2) + " << polynomials1[k][3] << "*(x) + " << polynomials1[k][4] << "*(y) + " << polynomials1[k][5] << ": 1/0\n";
            }
            
        }
    }

    scriptFile << "set xlabel 'x'\n";
    scriptFile << "set ylabel 'y'\n";
    scriptFile << "set zlabel 'z'\n";
    scriptFile << "set xrange[-" << x << ": " << x << "]\n";
    scriptFile << "set yrange[-" << y << ": " << y << "]\n";
    scriptFile << "set zrange[-100: 100]\n";
    scriptFile << "splot f(x, y) lc rgb 'green' ";

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2 * n; j++){                                           
            k = i * 2 * n + j;
            if(k % 2 == 0){
                scriptFile << ", p_" << k << "(x, y) lc rgb 'red' notitle";
            } else {
                scriptFile << ", p_" << k << "(x, y) lc rgb 'blue' notitle";
            }
        }
    }
    scriptFile.close();

    system("gnuplot plot_script.gp");


    for(int i = 0; i < 2 * n * n; i++){
        delete[] polynomials1[i];
        delete[] polynomials2[i];
        delete[] triangles_phi[i][0]; 
        delete[] triangles_phi[i][1]; 
        delete[] triangles_phi[i][2]; 
        delete[] triangles_phi[i][3]; 
        delete[] triangles_phi[i][4]; 
        delete[] triangles_phi[i][5]; 
        delete[] triangles_phi[i]; 
    }
    delete[] polynomials1;
    delete[] polynomials2;
    delete[] triangles_phi;
    return 0;
}

double function(double x, double y){
    return x*x-y*y+exp(x)*sin(x)/(x*x*x*x*x*x*x);
}

int interpolation(int n, double** coeff, double** storage, double*** triangles_phi, double x, double y){
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
            }else{                                //                       /|
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

            triangle_interpol(new_x1, new_y1, new_x2, new_y2, new_x3, new_y3, storage[k], triangles_phi[k]);
        }
    }

    double A[36];
    double b[6];
    double X[6];
    double buf;
    double b1_x;
    double b2_x;
    double b1_y;
    double b1_y_mult_x;
    double b2_y;
    double b2_y_mult_x;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2 * n; j++){
                                                  
            if(j%2 == 0){                         //                    ___
                x1 = -x + d_x * (j/2);            //  типа треугольник  | /
                y1 = y - d_y * i;                 //                    |/
                x2 = x1 + d_x;
                y2 = y1;
                x3 = x1;
                y3 = y1 - d_y;
            }else{                                //                       /|
                x1 = -x + d_x * ((j/2) + 1);      //  типа треугольник    /_|
                y1 = y - d_y * i;
                x2 = x1;
                y2 = y1 - d_y;
                x3 = x1 - d_x;
                y3 = y1 - d_y;
            }

            k = i * 2 * n + j;

            if(j%2 == 0){   
                b1_x = x1;
                b2_x = x2;
                b1_y = y3 - x3 * d_y / d_x;
                b1_y_mult_x = d_y / d_x;
                b2_y = y1;
                b2_y_mult_x = 0;    
            } else {
                b1_x = x2;
                b2_x = x3;
                b1_y = y3;
                b1_y_mult_x = 0;
                b2_y = y3 - x3 * d_y / d_x;
                b2_y_mult_x = d_y / d_x;
            }

            for(int u = 0; u < 6; u++){
                A[u * 6] = integral2(triangles_phi[k][u], triangles_phi[k][0], b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);
                A[u * 6 + 1] = integral2(triangles_phi[k][u], triangles_phi[k][1], b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);
                A[u * 6 + 2] = integral2(triangles_phi[k][u], triangles_phi[k][2], b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);
                A[u * 6 + 3] = integral2(triangles_phi[k][u], triangles_phi[k][3], b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);
                A[u * 6 + 4] = integral2(triangles_phi[k][u], triangles_phi[k][4], b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);
                A[u * 6 + 5] = integral2(triangles_phi[k][u], triangles_phi[k][5], b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);
                b[u] = integral2(triangles_phi[k][u], storage[k], b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);
                X[u] = 0;
            }
            solver(6, A, b, X);

            coeff[k][0] = 0;
            coeff[k][1] = 0;
            coeff[k][2] = 0;
            coeff[k][3] = 0;
            coeff[k][4] = 0;
            coeff[k][5] = 0;

            for(int u = 0; u < 6; u++){
                buf = X[u];
                coeff[k][0] += buf * triangles_phi[k][u][0];
                coeff[k][1] += buf * triangles_phi[k][u][1];
                coeff[k][2] += buf * triangles_phi[k][u][2];
                coeff[k][3] += buf * triangles_phi[k][u][3];
                coeff[k][4] += buf * triangles_phi[k][u][4];
                coeff[k][5] += buf * triangles_phi[k][u][5];
            }
        }
    }

    return 0;
}

void triangle_interpol(double x1, double y1, double x2, double y2, double x3, double y3, double* coeff, double** phi){
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
    phi[0][0] = (buf1[0]*buf2[0]);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    phi[0][1] += (buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    phi[0][2] += (buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    phi[0][3] += (buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    phi[0][4] += (buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    phi[0][5] += (buf1[2]*buf2[2]);
    coeff[5] += buf*(buf1[2]*buf2[2]);

    psi(x3, y3, x1, y1, x2, y2, buf1);
    psi(x4, y4, x6, y6, x2, y2, buf2);
    buf = function(x2, y2);
    phi[1][0] = (buf1[0]*buf2[0]);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    phi[1][1] += (buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    phi[1][2] += (buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    phi[1][3] += (buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    phi[1][4] += (buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    phi[1][5] += (buf1[2]*buf2[2]);
    coeff[5] += buf*(buf1[2]*buf2[2]);

    psi(x1, y1, x2, y2, x3, y3, buf1);
    psi(x5, y5, x4, y4, x3, y3, buf2);
    buf = function(x3, y3);
    phi[2][0] = (buf1[0]*buf2[0]);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    phi[2][1] += (buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    phi[2][2] += (buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    phi[2][3] += (buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    phi[2][4] += (buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    phi[2][5] += (buf1[2]*buf2[2]);
    coeff[5] += buf*(buf1[2]*buf2[2]);

    psi(x3, y3, x1, y1, x4, y4, buf1);
    psi(x2, y2, x1, y1, x4, y4, buf2);
    buf = function(x4, y4);
    phi[3][0] = (buf1[0]*buf2[0]);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    phi[3][1] += (buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    phi[3][2] += (buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    phi[3][3] += (buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    phi[3][4] += (buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    phi[3][5] += (buf1[2]*buf2[2]);
    coeff[5] += buf*(buf1[2]*buf2[2]);

    psi(x3, y3, x2, y2, x5, y5, buf1);
    psi(x2, y2, x1, y1, x5, y5, buf2);
    buf = function(x5, y5);
    phi[4][0] = (buf1[0]*buf2[0]);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    phi[4][1] += (buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    phi[4][2] += (buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    phi[4][3] += (buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    phi[4][4] += (buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    phi[4][5] += (buf1[2]*buf2[2]);
    coeff[5] += buf*(buf1[2]*buf2[2]);

    psi(x3, y3, x1, y1, x6, y6, buf1);
    psi(x2, y2, x3, y3, x6, y6, buf2);
    buf = function(x6, y6);
    phi[5][0] = (buf1[0]*buf2[0]);
    coeff[0] += buf*(buf1[0]*buf2[0]);
    phi[5][1] += (buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    coeff[1] += buf*(buf1[0]*buf2[1] + buf1[1]*buf2[0]);
    phi[5][2] += (buf1[1]*buf2[1]);
    coeff[2] += buf*(buf1[1]*buf2[1]);
    phi[5][3] += (buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    coeff[3] += buf*(buf1[0]*buf2[2] + buf1[2]*buf2[0]);
    phi[5][4] += (buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    coeff[4] += buf*(buf1[2]*buf2[1] + buf1[1]*buf2[2]);
    phi[5][5] += (buf1[2]*buf2[2]);
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
}

double integral(int pow_x, int pow_y, double b1_x, double b2_x, double b1_y, double b1_y_mult_x, double b2_y, double b2_y_mult_x){ // Интеграл по трапеции x^(pow_x) * y^(pow_y)
    double res = 0;
    if(pow_y == 0){
        res += (b2_y - b1_y) * (pow(b2_x, pow_x + 1) - pow(b1_x, pow_x + 1)) / (pow_x + 1);
        res += (b2_y_mult_x - b1_y_mult_x) * (pow(b2_x, pow_x + 2) - pow(b1_x, pow_x + 2)) / (pow_x + 2);
    }
    if(pow_y == 1){
        res += (b2_y * b2_y - b1_y * b1_y) * (pow(b2_x, pow_x + 1) - pow(b1_x, pow_x + 1)) / (pow_x + 1);
        res += 2 * (b2_y_mult_x * b2_y - b1_y_mult_x * b1_y) * (pow(b2_x, pow_x + 2) - pow(b1_x, pow_x + 2)) / (pow_x + 2);
        res += (b2_y_mult_x * b2_y_mult_x - b1_y_mult_x * b1_y_mult_x) * (pow(b2_x, pow_x + 3) - pow(b1_x, pow_x + 3)) / (pow_x + 3);
        res /= 2;
    }
    if(pow_y == 2){
        res += (b2_y * b2_y * b2_y - b1_y * b1_y * b1_y) * (pow(b2_x, pow_x + 1) - pow(b1_x, pow_x + 1)) / (pow_x + 1);
        res += 3 * (b2_y_mult_x * b2_y * b2_y - b1_y_mult_x * b1_y * b1_y) * (pow(b2_x, pow_x + 2) - pow(b1_x, pow_x + 2)) / (pow_x + 2);
        res += 3 * (b2_y_mult_x * b2_y_mult_x * b2_y - b1_y_mult_x * b1_y_mult_x * b1_y) * (pow(b2_x, pow_x + 3) - pow(b1_x, pow_x + 3)) / (pow_x + 3);
        res += (b2_y_mult_x * b2_y_mult_x * b2_y_mult_x - b1_y_mult_x * b1_y_mult_x * b1_y_mult_x) * (pow(b2_x, pow_x + 4) - pow(b1_x, pow_x + 4)) / (pow_x + 4);
        res /= 3;
    }
    if(pow_y == 3){
        res += (b2_y * b2_y * b2_y * b2_y - b1_y * b1_y * b1_y * b1_y) * (pow(b2_x, pow_x + 1) - pow(b1_x, pow_x + 1)) / (pow_x + 1);
        res += 4 * (b2_y_mult_x * b2_y * b2_y * b2_y - b1_y_mult_x * b1_y * b1_y * b1_y) * (pow(b2_x, pow_x + 2) - pow(b1_x, pow_x + 2)) / (pow_x + 2);
        res += 6 * (b2_y_mult_x * b2_y_mult_x * b2_y * b2_y - b1_y_mult_x * b1_y_mult_x * b1_y * b1_y) * (pow(b2_x, pow_x + 3) - pow(b1_x, pow_x + 3)) / (pow_x + 3);
        res += 4 * (b2_y_mult_x * b2_y_mult_x * b2_y_mult_x * b2_y - b1_y_mult_x * b1_y_mult_x * b1_y_mult_x * b1_y) * (pow(b2_x, pow_x + 4) - pow(b1_x, pow_x + 4)) / (pow_x + 4);
        res += (b2_y_mult_x * b2_y_mult_x * b2_y_mult_x * b2_y_mult_x - b1_y_mult_x * b1_y_mult_x * b1_y_mult_x * b1_y_mult_x) * (pow(b2_x, pow_x + 5) - pow(b1_x, pow_x + 5)) / (pow_x + 5);
        res /= 4;
    }
    if(pow_y == 4){
        res += (b2_y * b2_y * b2_y * b2_y * b2_y - b1_y * b1_y * b1_y * b1_y * b1_y) * (pow(b2_x, pow_x + 1) - pow(b1_x, pow_x + 1)) / (pow_x + 1);
        res += 5 * (b2_y_mult_x * b2_y * b2_y * b2_y * b2_y - b1_y_mult_x * b1_y * b1_y * b1_y * b1_y) * (pow(b2_x, pow_x + 2) - pow(b1_x, pow_x + 2)) / (pow_x + 2);
        res += 10 * (b2_y_mult_x * b2_y_mult_x * b2_y * b2_y * b2_y - b1_y_mult_x * b1_y_mult_x * b1_y * b1_y * b1_y) * (pow(b2_x, pow_x + 3) - pow(b1_x, pow_x + 3)) / (pow_x + 3);
        res += 10 * (b2_y_mult_x * b2_y_mult_x * b2_y_mult_x * b2_y * b2_y - b1_y_mult_x * b1_y_mult_x * b1_y_mult_x * b1_y * b1_y) * (pow(b2_x, pow_x + 4) - pow(b1_x, pow_x + 4)) / (pow_x + 4);
        res += 5 * (b2_y_mult_x * b2_y_mult_x * b2_y_mult_x * b2_y_mult_x * b2_y- b1_y_mult_x * b1_y_mult_x * b1_y_mult_x * b1_y_mult_x * b1_y) * (pow(b2_x, pow_x + 5) - pow(b1_x, pow_x + 5)) / (pow_x + 5);
        res += (b2_y_mult_x * b2_y_mult_x * b2_y_mult_x * b2_y_mult_x * b2_y_mult_x - b1_y_mult_x * b1_y_mult_x * b1_y_mult_x * b1_y_mult_x * b1_y_mult_x) * (pow(b2_x, pow_x + 5) - pow(b1_x, pow_x + 5)) / (pow_x + 5);
        res /= 5;
    }
    return res;
}

double integral2(double* pol1, double* pol2, double b1_x, double b2_x, double b1_y, double b1_y_mult_x, double b2_y, double b2_y_mult_x){  //Два многочлена степени 2 
    double res = 0;
    double buf;

    buf = pol1[0] * pol2[0];
    res += buf * integral(4, 0, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[2] * pol2[2];
    res += buf * integral(0, 4, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[0] * pol2[1] + pol1[1] * pol2[0];
    res += buf * integral(3, 1, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[2] * pol2[1] + pol1[1] * pol2[2];
    res += buf * integral(1, 3, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[0] * pol2[2] + pol1[2] * pol2[0] + pol1[1] * pol2[1];
    res += buf * integral(2, 2, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[0] * pol2[3] + pol1[3] * pol2[0];
    res += buf * integral(3, 0, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[2] * pol2[4] + pol1[4] * pol2[2];
    res += buf * integral(0, 3, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[0] * pol2[4] + pol1[4] * pol2[0] + pol1[1] * pol2[3] + pol1[3] * pol2[1];
    res += buf * integral(2, 1, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[2] * pol2[3] + pol1[3] * pol2[2] + pol1[1] * pol2[4] + pol1[4] * pol2[1];
    res += buf * integral(1, 2, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[0] * pol2[5] + pol1[5] * pol2[0] + pol1[3] * pol2[3];
    res += buf * integral(2, 0, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[2] * pol2[5] + pol1[5] * pol2[2] + pol1[4] * pol2[4];
    res += buf * integral(0, 2, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[1] * pol2[5] + pol1[5] * pol2[1] + pol1[3] * pol2[4] + pol1[4] * pol2[3];
    res += buf * integral(1, 1, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[3] * pol2[5] + pol1[5] * pol2[3];
    res += buf * integral(1, 0, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[4] * pol2[5] + pol1[5] * pol2[4];
    res += buf * integral(0, 1, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    buf = pol1[5] * pol2[5];
    res += buf * integral(0, 0, b1_x, b2_x, b1_y, b1_y_mult_x, b2_y, b2_y_mult_x);

    return res;
}
