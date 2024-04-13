
/* Построить линейную интерполяцию x^3 в линейном пространстве

< Cot(x)/2 + Sin(x)^2, Cot(x)/8, -x + 16x^2 / Pi, x >
через точки
{ -Pi/4, Pi/4, 3*Pi/2, Pi/2 }

*/

#include <fstream>
#include <cmath>
#include "solver_H.h"

int main(void){
    double x;
    double* points;
    points = new double[4];
    points[0] = - M_PI / 4;
    points[1] = M_PI / 4;
    points[2] = 3 * M_PI / 2;
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
        return -1;
    }

    std::ofstream dataFile("data.txt");
    for (int i = 0; i < 4; i++){
        x = points[i];
        double y_interpolation = Res[0] * (cos(x) / (2 * sin(x)) + pow(sin(x), 2)) +
                                + Res[1] * (cos(x) / (8 * sin(x))) +
                                + Res[2] * (-x + 16 * pow(x, 2) / M_PI) +
                                + Res[3] * (x);
        double y_cubed = pow(x, 3);
        dataFile << x << " " << y_interpolation << " " << y_cubed << "\n";
    
    }
    dataFile.close();

    std::ofstream scriptFile("plot_script.gp");
    scriptFile << "set terminal pngcairo enhanced color size 800,600\n";
    scriptFile << "set output 'interpolation_plot.png'\n";
    scriptFile << "a = " << Res[0] << "\n";
    scriptFile << "b = " << Res[1] << "\n";
    scriptFile << "c = " << Res[2] << "\n";
    scriptFile << "d = " << Res[3] << "\n";
    scriptFile << "f(x) = a * (cos(x) / (2 * sin(x)) + sin(x)**2) + b * (cos(x) / (8 * sin(x))) + c * (-x + 16 * x**2 / pi) + d * (x)\n";
    scriptFile << "g(x) = x**3\n";
    scriptFile << "set xlabel 'x'\n";
    scriptFile << "set ylabel 'y'\n";
    scriptFile << "set grid\n";
    scriptFile << "set xrange[-pi/2: 2*pi]\n";
    scriptFile << "set yrange[-(pi/2)**3: (2*pi)**3]\n";
    scriptFile << "set title 'Линейная интерполяция x^3'\n";
    scriptFile << "plot f(x) title 'Interpolation'  lc rgb 'blue',\
                        g(x) title 'X^3'  lc rgb 'black',\
                             'data.txt' using 1:3 with points title 'key points' lc rgb 'red'\n";
    scriptFile.close();

    system("gnuplot plot_script.gp");

    delete[] points;
    delete[] Res;
    delete[] b;
    delete[] A;
    return 0;
}
