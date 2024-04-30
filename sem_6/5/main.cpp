
/* Приближение функции, заданной в эллипсе, 
конечными элементами степени 3

a*x^3 + b*x^2*y + c*x*y^2 + d*y^3 + e*x^2 + f*xy + g*y^2 + h*x + k*y + l

*/

#include <fstream>
#include <iostream>
#include <cmath>

double function(double x, double y);

int interpolation(int n, double** coeff, double x, double y);

void triangle_interpol(double x1, double y1, double x2, double y2, double x3, double y3, double* coeff);
    
void psi(double x1, double y1, double x2, double y2, double x0, double y0, double* coeff);

int main(void){
    int n = 1;
    double x = 1;
    double y = 1;
    std::cin >> n >> x >> y;
    x = fabs(x);
    y = fabs(y);
    if(n < 1) return -1;
    double** polynomials;
    polynomials = new double *[2 * n * n]; 
    for(int i = 0; i < 2 * n * n; i++){
        polynomials[i] = new double [10]; 
        for(int j = 0; j < 10; j++){
            polynomials[i][j] = 0; 
        }
    }

    interpolation(n, polynomials, x, y);

    std::ofstream scriptFile("plot_script.gp");
    scriptFile << "set terminal pngcairo enhanced color size 1000,1000\n";
    scriptFile << "set output 'Triangulation.png'\n";
    scriptFile << "f(x, y) =  (x*y*x*y*x) \n";
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
                scriptFile << "p_" << k << "(x, y) =  ( (x/" << x << ")**2 + (y/" << y << ")**2 > 1) ? 1/0 : ("<< x1 <<" < x && x < "<< x1 + d_x << " && (" << y1 - d_y << " + " << d_y / d_x << "*(x - " << x1 << ")) < y && y < " << y1 << ") ? " << polynomials[k][0] << "*(x**3) + " << polynomials[k][1] << "*(x*x*y) + " << polynomials[k][2] << "*(x*y*y) + " << polynomials[k][3] << "*(y**3) + " << polynomials[k][4] << "*(x**2) + " << polynomials[k][5] << "*(x*y) + " << polynomials[k][6] << "*(y**2) + " << polynomials[k][7] << "*(x) + " << polynomials[k][8] << "*(y) + " << polynomials[k][9] << ": 1/0\n";
            }else{    
                x1 = -x + d_x * ((j/2) + 1);  
                y1 = y - d_y * i;                     
                scriptFile << "p_" << k << "(x, y) =  ( (x/" << x << ")**2 + (y/" << y << ")**2 > 1) ? 1/0 : ("<< x1 - d_x <<" < x && x < "<< x1 <<" && " << y1 - d_y << " < y && y < (" << y1 - d_y << " + " << d_y / d_x << "*(x - " << x1 - d_x << "))) ? " << polynomials[k][0] << "*(x**3) + " << polynomials[k][1] << "*(x*x*y) + " << polynomials[k][2] << "*(x*y*y) + " << polynomials[k][3] << "*(y**3) + " << polynomials[k][4] << "*(x**2) + " << polynomials[k][5] << "*(x*y) + " << polynomials[k][6] << "*(y**2) + " << polynomials[k][7] << "*(x) + " << polynomials[k][8] << "*(y) + " << polynomials[k][9] << ": 1/0\n";
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
        delete[] polynomials[i];
    }
    delete[] polynomials;
    return 0;
}

double function(double x, double y){
    return (x*y*x*y*x);
}

int interpolation(int n, double** coeff, double x, double y){
    double d_x = 2 * x / n;
    double d_y = 2 * y / n;
    double x1, x2, x3, y1, y2, y3;
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


            k = i * 2 * n + j;

            triangle_interpol(x1, y1, x2, y2, x3, y3, coeff[k]);
        }
    }

    return 0;
}

void triangle_interpol(double x1, double y1, double x2, double y2, double x3, double y3, double* coeff){
    for(int j = 0; j < 10; j++){
        coeff[j] = 0;         
    }

    double x4 = (2 * x1 + x2)/3;            //   1   4   5   2
    double y4 = (2 * y1 + y2)/3;            //   9   10  6
    double x5 = (2 * x2 + x1)/3;            //   8   7
    double y5 = (2 * y2 + y1)/3;            //   3

    double x6 = (2 * x2 + x3)/3;
    double y6 = (2 * y2 + y3)/3;
    double x7 = (2 * x3 + x2)/3;
    double y7 = (2 * y3 + y2)/3;

    double x8 = (2 * x3 + x1)/3;
    double y8 = (2 * y3 + y1)/3;
    double x9 = (2 * x1 + x3)/3;
    double y9 = (2 * y1 + y3)/3;

    double x10 = (x1 + x2 + x3)/3;
    double y10 = (y1 + y2 + y3)/3;

    double buf;
    double buf1[3];
    double buf2[3];
    double buf3[3];

    psi(x3, y3, x2, y2, x1, y1, buf1);
    psi(x8, y8, x5, y5, x1, y1, buf2);
    psi(x9, y9, x4, y4, x1, y1, buf3);
    buf = function(x1, y1);
    coeff[0] += buf*(buf1[0]*buf2[0]*buf3[0]);
    coeff[1] += buf*(buf1[0]*buf2[0]*buf3[1] + buf1[1]*buf2[0]*buf3[0] + buf1[0]*buf2[1]*buf3[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]*buf3[0] + buf1[0]*buf2[1]*buf3[1] + buf1[1]*buf2[0]*buf3[1]);
    coeff[3] += buf*(buf1[1]*buf2[1]*buf3[1]);
    coeff[4] += buf*(buf1[0]*buf2[0]*buf3[2] + buf1[2]*buf2[0]*buf3[0] + buf1[0]*buf2[2]*buf3[0]);
    coeff[5] += buf*(buf1[0]*buf2[1]*buf3[2] + buf1[2]*buf2[0]*buf3[1] + buf1[1]*buf2[2]*buf3[0] + buf1[1]*buf2[0]*buf3[2] + buf1[2]*buf2[1]*buf3[0] + buf1[0]*buf2[2]*buf3[1]);
    coeff[6] += buf*(buf1[1]*buf2[1]*buf3[2] + buf1[2]*buf2[1]*buf3[1] + buf1[1]*buf2[2]*buf3[1]);
    coeff[7] += buf*(buf1[0]*buf2[2]*buf3[2] + buf1[2]*buf2[0]*buf3[2] + buf1[2]*buf2[2]*buf3[0]);
    coeff[8] += buf*(buf1[1]*buf2[2]*buf3[2] + buf1[2]*buf2[1]*buf3[2] + buf1[2]*buf2[2]*buf3[1]);
    coeff[9] += buf*(buf1[2]*buf2[2]*buf3[2]);

    psi(x3, y3, x1, y1, x2, y2, buf1);
    psi(x6, y6, x5, y5, x2, y2, buf2);
    psi(x7, y7, x4, y4, x2, y2, buf3);
    buf = function(x2, y2);
    coeff[0] += buf*(buf1[0]*buf2[0]*buf3[0]);
    coeff[1] += buf*(buf1[0]*buf2[0]*buf3[1] + buf1[1]*buf2[0]*buf3[0] + buf1[0]*buf2[1]*buf3[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]*buf3[0] + buf1[0]*buf2[1]*buf3[1] + buf1[1]*buf2[0]*buf3[1]);
    coeff[3] += buf*(buf1[1]*buf2[1]*buf3[1]);
    coeff[4] += buf*(buf1[0]*buf2[0]*buf3[2] + buf1[2]*buf2[0]*buf3[0] + buf1[0]*buf2[2]*buf3[0]);
    coeff[5] += buf*(buf1[0]*buf2[1]*buf3[2] + buf1[2]*buf2[0]*buf3[1] + buf1[1]*buf2[2]*buf3[0] + buf1[1]*buf2[0]*buf3[2] + buf1[2]*buf2[1]*buf3[0] + buf1[0]*buf2[2]*buf3[1]);
    coeff[6] += buf*(buf1[1]*buf2[1]*buf3[2] + buf1[2]*buf2[1]*buf3[1] + buf1[1]*buf2[2]*buf3[1]);
    coeff[7] += buf*(buf1[0]*buf2[2]*buf3[2] + buf1[2]*buf2[0]*buf3[2] + buf1[2]*buf2[2]*buf3[0]);
    coeff[8] += buf*(buf1[1]*buf2[2]*buf3[2] + buf1[2]*buf2[1]*buf3[2] + buf1[2]*buf2[2]*buf3[1]);
    coeff[9] += buf*(buf1[2]*buf2[2]*buf3[2]);

    psi(x1, y1, x2, y2, x3, y3, buf1);
    psi(x8, y8, x7, y7, x3, y3, buf2);
    psi(x9, y9, x6, y6, x3, y3, buf3);
    buf = function(x3, y3);
    coeff[0] += buf*(buf1[0]*buf2[0]*buf3[0]);
    coeff[1] += buf*(buf1[0]*buf2[0]*buf3[1] + buf1[1]*buf2[0]*buf3[0] + buf1[0]*buf2[1]*buf3[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]*buf3[0] + buf1[0]*buf2[1]*buf3[1] + buf1[1]*buf2[0]*buf3[1]);
    coeff[3] += buf*(buf1[1]*buf2[1]*buf3[1]);
    coeff[4] += buf*(buf1[0]*buf2[0]*buf3[2] + buf1[2]*buf2[0]*buf3[0] + buf1[0]*buf2[2]*buf3[0]);
    coeff[5] += buf*(buf1[0]*buf2[1]*buf3[2] + buf1[2]*buf2[0]*buf3[1] + buf1[1]*buf2[2]*buf3[0] + buf1[1]*buf2[0]*buf3[2] + buf1[2]*buf2[1]*buf3[0] + buf1[0]*buf2[2]*buf3[1]);
    coeff[6] += buf*(buf1[1]*buf2[1]*buf3[2] + buf1[2]*buf2[1]*buf3[1] + buf1[1]*buf2[2]*buf3[1]);
    coeff[7] += buf*(buf1[0]*buf2[2]*buf3[2] + buf1[2]*buf2[0]*buf3[2] + buf1[2]*buf2[2]*buf3[0]);
    coeff[8] += buf*(buf1[1]*buf2[2]*buf3[2] + buf1[2]*buf2[1]*buf3[2] + buf1[2]*buf2[2]*buf3[1]);
    coeff[9] += buf*(buf1[2]*buf2[2]*buf3[2]);

    psi(x3, y3, x1, y1, x4, y4, buf1);
    psi(x8, y8, x5, y5, x4, y4, buf2);
    psi(x3, y3, x2, y2, x4, y4, buf3);
    buf = function(x4, y4);
    coeff[0] += buf*(buf1[0]*buf2[0]*buf3[0]);
    coeff[1] += buf*(buf1[0]*buf2[0]*buf3[1] + buf1[1]*buf2[0]*buf3[0] + buf1[0]*buf2[1]*buf3[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]*buf3[0] + buf1[0]*buf2[1]*buf3[1] + buf1[1]*buf2[0]*buf3[1]);
    coeff[3] += buf*(buf1[1]*buf2[1]*buf3[1]);
    coeff[4] += buf*(buf1[0]*buf2[0]*buf3[2] + buf1[2]*buf2[0]*buf3[0] + buf1[0]*buf2[2]*buf3[0]);
    coeff[5] += buf*(buf1[0]*buf2[1]*buf3[2] + buf1[2]*buf2[0]*buf3[1] + buf1[1]*buf2[2]*buf3[0] + buf1[1]*buf2[0]*buf3[2] + buf1[2]*buf2[1]*buf3[0] + buf1[0]*buf2[2]*buf3[1]);
    coeff[6] += buf*(buf1[1]*buf2[1]*buf3[2] + buf1[2]*buf2[1]*buf3[1] + buf1[1]*buf2[2]*buf3[1]);
    coeff[7] += buf*(buf1[0]*buf2[2]*buf3[2] + buf1[2]*buf2[0]*buf3[2] + buf1[2]*buf2[2]*buf3[0]);
    coeff[8] += buf*(buf1[1]*buf2[2]*buf3[2] + buf1[2]*buf2[1]*buf3[2] + buf1[2]*buf2[2]*buf3[1]);
    coeff[9] += buf*(buf1[2]*buf2[2]*buf3[2]);

    psi(x3, y3, x1, y1, x5, y5, buf1);
    psi(x7, y7, x4, y4, x5, y5, buf2);
    psi(x3, y3, x2, y2, x5, y5, buf3);
    buf = function(x5, y5);
    coeff[0] += buf*(buf1[0]*buf2[0]*buf3[0]);
    coeff[1] += buf*(buf1[0]*buf2[0]*buf3[1] + buf1[1]*buf2[0]*buf3[0] + buf1[0]*buf2[1]*buf3[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]*buf3[0] + buf1[0]*buf2[1]*buf3[1] + buf1[1]*buf2[0]*buf3[1]);
    coeff[3] += buf*(buf1[1]*buf2[1]*buf3[1]);
    coeff[4] += buf*(buf1[0]*buf2[0]*buf3[2] + buf1[2]*buf2[0]*buf3[0] + buf1[0]*buf2[2]*buf3[0]);
    coeff[5] += buf*(buf1[0]*buf2[1]*buf3[2] + buf1[2]*buf2[0]*buf3[1] + buf1[1]*buf2[2]*buf3[0] + buf1[1]*buf2[0]*buf3[2] + buf1[2]*buf2[1]*buf3[0] + buf1[0]*buf2[2]*buf3[1]);
    coeff[6] += buf*(buf1[1]*buf2[1]*buf3[2] + buf1[2]*buf2[1]*buf3[1] + buf1[1]*buf2[2]*buf3[1]);
    coeff[7] += buf*(buf1[0]*buf2[2]*buf3[2] + buf1[2]*buf2[0]*buf3[2] + buf1[2]*buf2[2]*buf3[0]);
    coeff[8] += buf*(buf1[1]*buf2[2]*buf3[2] + buf1[2]*buf2[1]*buf3[2] + buf1[2]*buf2[2]*buf3[1]);
    coeff[9] += buf*(buf1[2]*buf2[2]*buf3[2]);

    psi(x3, y3, x1, y1, x6, y6, buf1);
    psi(x4, y4, x7, y7, x6, y6, buf2);
    psi(x1, y1, x2, y2, x6, y6, buf3);
    buf = function(x6, y6);
    coeff[0] += buf*(buf1[0]*buf2[0]*buf3[0]);
    coeff[1] += buf*(buf1[0]*buf2[0]*buf3[1] + buf1[1]*buf2[0]*buf3[0] + buf1[0]*buf2[1]*buf3[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]*buf3[0] + buf1[0]*buf2[1]*buf3[1] + buf1[1]*buf2[0]*buf3[1]);
    coeff[3] += buf*(buf1[1]*buf2[1]*buf3[1]);
    coeff[4] += buf*(buf1[0]*buf2[0]*buf3[2] + buf1[2]*buf2[0]*buf3[0] + buf1[0]*buf2[2]*buf3[0]);
    coeff[5] += buf*(buf1[0]*buf2[1]*buf3[2] + buf1[2]*buf2[0]*buf3[1] + buf1[1]*buf2[2]*buf3[0] + buf1[1]*buf2[0]*buf3[2] + buf1[2]*buf2[1]*buf3[0] + buf1[0]*buf2[2]*buf3[1]);
    coeff[6] += buf*(buf1[1]*buf2[1]*buf3[2] + buf1[2]*buf2[1]*buf3[1] + buf1[1]*buf2[2]*buf3[1]);
    coeff[7] += buf*(buf1[0]*buf2[2]*buf3[2] + buf1[2]*buf2[0]*buf3[2] + buf1[2]*buf2[2]*buf3[0]);
    coeff[8] += buf*(buf1[1]*buf2[2]*buf3[2] + buf1[2]*buf2[1]*buf3[2] + buf1[2]*buf2[2]*buf3[1]);
    coeff[9] += buf*(buf1[2]*buf2[2]*buf3[2]);

    psi(x3, y3, x1, y1, x7, y7, buf1);
    psi(x9, y9, x6, y6, x7, y7, buf2);
    psi(x1, y1, x2, y2, x7, y7, buf3);
    buf = function(x7, y7);
    coeff[0] += buf*(buf1[0]*buf2[0]*buf3[0]);
    coeff[1] += buf*(buf1[0]*buf2[0]*buf3[1] + buf1[1]*buf2[0]*buf3[0] + buf1[0]*buf2[1]*buf3[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]*buf3[0] + buf1[0]*buf2[1]*buf3[1] + buf1[1]*buf2[0]*buf3[1]);
    coeff[3] += buf*(buf1[1]*buf2[1]*buf3[1]);
    coeff[4] += buf*(buf1[0]*buf2[0]*buf3[2] + buf1[2]*buf2[0]*buf3[0] + buf1[0]*buf2[2]*buf3[0]);
    coeff[5] += buf*(buf1[0]*buf2[1]*buf3[2] + buf1[2]*buf2[0]*buf3[1] + buf1[1]*buf2[2]*buf3[0] + buf1[1]*buf2[0]*buf3[2] + buf1[2]*buf2[1]*buf3[0] + buf1[0]*buf2[2]*buf3[1]);
    coeff[6] += buf*(buf1[1]*buf2[1]*buf3[2] + buf1[2]*buf2[1]*buf3[1] + buf1[1]*buf2[2]*buf3[1]);
    coeff[7] += buf*(buf1[0]*buf2[2]*buf3[2] + buf1[2]*buf2[0]*buf3[2] + buf1[2]*buf2[2]*buf3[0]);
    coeff[8] += buf*(buf1[1]*buf2[2]*buf3[2] + buf1[2]*buf2[1]*buf3[2] + buf1[2]*buf2[2]*buf3[1]);
    coeff[9] += buf*(buf1[2]*buf2[2]*buf3[2]);

    psi(x3, y3, x2, y2, x8, y8, buf1);
    psi(x9, y9, x6, y6, x8, y8, buf2);
    psi(x1, y1, x2, y2, x8, y8, buf3);
    buf = function(x8, y8);
    coeff[0] += buf*(buf1[0]*buf2[0]*buf3[0]);
    coeff[1] += buf*(buf1[0]*buf2[0]*buf3[1] + buf1[1]*buf2[0]*buf3[0] + buf1[0]*buf2[1]*buf3[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]*buf3[0] + buf1[0]*buf2[1]*buf3[1] + buf1[1]*buf2[0]*buf3[1]);
    coeff[3] += buf*(buf1[1]*buf2[1]*buf3[1]);
    coeff[4] += buf*(buf1[0]*buf2[0]*buf3[2] + buf1[2]*buf2[0]*buf3[0] + buf1[0]*buf2[2]*buf3[0]);
    coeff[5] += buf*(buf1[0]*buf2[1]*buf3[2] + buf1[2]*buf2[0]*buf3[1] + buf1[1]*buf2[2]*buf3[0] + buf1[1]*buf2[0]*buf3[2] + buf1[2]*buf2[1]*buf3[0] + buf1[0]*buf2[2]*buf3[1]);
    coeff[6] += buf*(buf1[1]*buf2[1]*buf3[2] + buf1[2]*buf2[1]*buf3[1] + buf1[1]*buf2[2]*buf3[1]);
    coeff[7] += buf*(buf1[0]*buf2[2]*buf3[2] + buf1[2]*buf2[0]*buf3[2] + buf1[2]*buf2[2]*buf3[0]);
    coeff[8] += buf*(buf1[1]*buf2[2]*buf3[2] + buf1[2]*buf2[1]*buf3[2] + buf1[2]*buf2[2]*buf3[1]);
    coeff[9] += buf*(buf1[2]*buf2[2]*buf3[2]);

    psi(x3, y3, x2, y2, x9, y9, buf1);
    psi(x5, y5, x8, y8, x9, y9, buf2);
    psi(x1, y1, x2, y2, x9, y9, buf3);
    buf = function(x9, y9);
    coeff[0] += buf*(buf1[0]*buf2[0]*buf3[0]);
    coeff[1] += buf*(buf1[0]*buf2[0]*buf3[1] + buf1[1]*buf2[0]*buf3[0] + buf1[0]*buf2[1]*buf3[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]*buf3[0] + buf1[0]*buf2[1]*buf3[1] + buf1[1]*buf2[0]*buf3[1]);
    coeff[3] += buf*(buf1[1]*buf2[1]*buf3[1]);
    coeff[4] += buf*(buf1[0]*buf2[0]*buf3[2] + buf1[2]*buf2[0]*buf3[0] + buf1[0]*buf2[2]*buf3[0]);
    coeff[5] += buf*(buf1[0]*buf2[1]*buf3[2] + buf1[2]*buf2[0]*buf3[1] + buf1[1]*buf2[2]*buf3[0] + buf1[1]*buf2[0]*buf3[2] + buf1[2]*buf2[1]*buf3[0] + buf1[0]*buf2[2]*buf3[1]);
    coeff[6] += buf*(buf1[1]*buf2[1]*buf3[2] + buf1[2]*buf2[1]*buf3[1] + buf1[1]*buf2[2]*buf3[1]);
    coeff[7] += buf*(buf1[0]*buf2[2]*buf3[2] + buf1[2]*buf2[0]*buf3[2] + buf1[2]*buf2[2]*buf3[0]);
    coeff[8] += buf*(buf1[1]*buf2[2]*buf3[2] + buf1[2]*buf2[1]*buf3[2] + buf1[2]*buf2[2]*buf3[1]);
    coeff[9] += buf*(buf1[2]*buf2[2]*buf3[2]);

    psi(x3, y3, x2, y2, x10, y10, buf1);
    psi(x2, y2, x1, y1, x10, y10, buf2);
    psi(x1, y1, x3, y3, x10, y10, buf3);
    buf = function(x10, y10);
    coeff[0] += buf*(buf1[0]*buf2[0]*buf3[0]);
    coeff[1] += buf*(buf1[0]*buf2[0]*buf3[1] + buf1[1]*buf2[0]*buf3[0] + buf1[0]*buf2[1]*buf3[0]);
    coeff[2] += buf*(buf1[1]*buf2[1]*buf3[0] + buf1[0]*buf2[1]*buf3[1] + buf1[1]*buf2[0]*buf3[1]);
    coeff[3] += buf*(buf1[1]*buf2[1]*buf3[1]);
    coeff[4] += buf*(buf1[0]*buf2[0]*buf3[2] + buf1[2]*buf2[0]*buf3[0] + buf1[0]*buf2[2]*buf3[0]);
    coeff[5] += buf*(buf1[0]*buf2[1]*buf3[2] + buf1[2]*buf2[0]*buf3[1] + buf1[1]*buf2[2]*buf3[0] + buf1[1]*buf2[0]*buf3[2] + buf1[2]*buf2[1]*buf3[0] + buf1[0]*buf2[2]*buf3[1]);
    coeff[6] += buf*(buf1[1]*buf2[1]*buf3[2] + buf1[2]*buf2[1]*buf3[1] + buf1[1]*buf2[2]*buf3[1]);
    coeff[7] += buf*(buf1[0]*buf2[2]*buf3[2] + buf1[2]*buf2[0]*buf3[2] + buf1[2]*buf2[2]*buf3[0]);
    coeff[8] += buf*(buf1[1]*buf2[2]*buf3[2] + buf1[2]*buf2[1]*buf3[2] + buf1[2]*buf2[2]*buf3[1]);
    coeff[9] += buf*(buf1[2]*buf2[2]*buf3[2]);
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
