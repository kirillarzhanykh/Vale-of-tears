
/* 

Облако точек в R^3 задано в виде матрицы 3×n. Найти 3 главные компоненты (направления) метода PCA, посчитать квадраты дисперсии данных вдоль каждой компоненты
 и нарисовать центрированное облако точек и компоненты (в виде стрелочек) в R^3.

*/

#include <fstream>
#include <iostream>
#include <cmath>
#include "solver_H.h"
#include "eigenvalues_QR.h"

int main(void){
    double** points;
    double new_zero[3];
    new_zero[0] = 0;
    new_zero[1] = 0;
    new_zero[2] = 0;

    std::ifstream dataFile("data.txt");

    points = new double *[25]; //5 точек

    for(int i = 0; i < 25; i++){
        points[i] = new double [3];
        dataFile >> points[i][0];
        dataFile >> points[i][1];
        dataFile >> points[i][2];
        new_zero[0] += points[i][0];
        new_zero[1] += points[i][1];
        new_zero[2] += points[i][2];
    }

    new_zero[0] /= 25;
    new_zero[1] /= 25;
    new_zero[2] /= 25;

    for(int i = 0; i < 25; i++){
        points[i][0] -= new_zero[0];
        points[i][1] -= new_zero[1];
        points[i][2] -= new_zero[2];
    }

    double cov[9];
    for(int k = 0; k < 3; k++){
        for(int m = 0; m < 3; m++){
            cov[3 * k + m] = 0;
            for(int i = 0; i < 25; i++){
                cov[3 * k + m] += points[i][k] * points[i][m];
                cov[3 * k + m] /= 24;
            }
            std::cout << cov[3 * k + m] << " " ;
        }
        std::cout << "\n" ;
    }
    



    dataFile.close();
    /*
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

    for(int i = 0; i < 25; i++){
        delete[] points[i];
    }
    delete[] points;
    */
   
    return 0;
}
