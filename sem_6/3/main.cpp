
/* 

Облако точек в R^3 задано в виде матрицы 3×n. Найти 3 главные компоненты (направления) метода PCA, посчитать квадраты дисперсии данных вдоль каждой компоненты
 и нарисовать центрированное облако точек и компоненты (в виде стрелочек) в R^3.

*/

#include <fstream>
#include <iostream>
#include <cmath>
#include "eigenvalues_QR.h"

int find_vector(int n, double* A, double* x);

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

    dataFile.close();

    new_zero[0] /= 25;
    new_zero[1] /= 25;
    new_zero[2] /= 25;

    for(int i = 0; i < 25; i++){
        points[i][0] -= new_zero[0];
        points[i][1] -= new_zero[1];
        points[i][2] -= new_zero[2];
    }

    double cov[9];

    //Эти переменные чисто технические - для работы метода
    double A[9];
    double B[9];
    double EigenValues[5];

    for(int k = 0; k < 3; k++){
        for(int m = 0; m < 3; m++){
            cov[3 * k + m] = 0;
            for(int i = 0; i < 25; i++){
                cov[3 * k + m] += points[i][k] * points[i][m];
            }
            cov[3 * k + m] /= 24;
            A[3 * k + m] = cov[3 * k + m];
        }
    }
    
    eigenvalues(3, A, B, EigenValues, 1e-17);

    double buf;
    for(int k = 0; k < 3; k++){
        for(int m = k; m < 3; m++){
            if(EigenValues[k] < EigenValues[m]){
                buf = EigenValues[k];
                EigenValues[k] = EigenValues[m];
                EigenValues[m] = buf;
            }
        }
    }

    double v1[3], v2[3], v3[3];

    for(int k = 0; k < 3; k++){
        for(int m = 0; m < 3; m++){
            A[3 * k + m] = cov[3 * k + m];
            if(k == m) A[3 * k + m] -= EigenValues[0];
        }
    }
    find_vector(3, A, v1);
    

    for(int k = 0; k < 3; k++){
        for(int m = 0; m < 3; m++){
            A[3 * k + m] = cov[3 * k + m];
            if(k == m) A[3 * k + m] -= EigenValues[1];
        }
    }
    find_vector(3, A, v2);
    
    for(int k = 0; k < 3; k++){
        for(int m = 0; m < 3; m++){
            A[3 * k + m] = cov[3 * k + m];
            if(k == m) A[3 * k + m] -= EigenValues[2];
        }
    }
    find_vector(3, A, v3);
    
    double dysp = 0;
    for(int i = 0; i < 25; i++){
        dysp += points[i][0] * points[i][0];
        dysp += points[i][1] * points[i][1];
        dysp += points[i][2] * points[i][2];
    }

    double dysp1 = 0;
    for(int i = 0; i < 25; i++){
        buf = points[i][0] * v1[0] + points[i][1] * v1[1] + points[i][2] * v1[2];
        dysp1 += buf * buf;
    }

    double dysp2 = 0;
    for(int i = 0; i < 25; i++){
        buf = points[i][0] * v2[0] + points[i][1] * v2[1] + points[i][2] * v2[2];
        dysp2 += buf * buf;
    }

    double dysp3 = 0;
    for(int i = 0; i < 25; i++){
        buf = points[i][0] * v3[0] + points[i][1] * v3[1] + points[i][2] * v3[2];
        dysp3 += buf * buf;
    }

    std::cout << "Квадрат дисперсии: " << dysp << std::endl;
    std::cout << "Квадрат дисперсии вдоль первой компоненты: " << dysp1 << std::endl;
    std::cout << "Квадрат дисперсии вдоль второй компоненты: " << dysp2 << std::endl;
    std::cout << "Квадрат дисперсии вдоль третьей компоненты: " << dysp3 << std::endl;

    
    std::ofstream scriptFile("plot_script.gp");
    scriptFile << "set terminal pngcairo enhanced color size 1000,1000\n";
    scriptFile << "set output 'PCA.png'\n";

    scriptFile << "x0 = " << new_zero[0] << "\n";
    scriptFile << "y0 = " << new_zero[1] << "\n";
    scriptFile << "z0 = " << new_zero[2] << "\n";

    scriptFile << "x1 = " << 4 * v1[0] << "\n";
    scriptFile << "y1 = " << 4 * v1[1] << "\n";
    scriptFile << "z1 = " << 4 * v1[2] << "\n";
    scriptFile << "x2 = " << 2 * v2[0] << "\n";
    scriptFile << "y2 = " << 2 * v2[1] << "\n";
    scriptFile << "z2 = " << 2 * v2[2] << "\n";
    scriptFile << "x3 = " << v3[0] << "\n";
    scriptFile << "y3 = " << v3[1] << "\n";
    scriptFile << "z3 = " << v3[2] << "\n";

    scriptFile << "set xlabel 'x'\n";
    scriptFile << "set ylabel 'y'\n";
    scriptFile << "set zlabel 'z'\n";
    scriptFile << "set view 50, 200\n";
    scriptFile << "set arrow 1 from x0, y0, z0 to x0 + x1, y0 + y1, z0 + z1 lc rgb 'blue'\n";
    scriptFile << "set arrow 2 from x0, y0, z0 to x0 + x2, y0 + y2, z0 + z2 lc rgb 'red'\n";
    scriptFile << "set arrow 3 from x0, y0, z0 to x0 + x3, y0 + y3, z0 + z3 lc rgb 'green'\n";
    scriptFile << "splot -(((x - x0)*x3 + (y - y0)*y3)/z3 + z0) title 'approximative plane' lc rgb 'grey',\
                    'data.txt' using 1:2:3 with points title 'points' lc rgb 'black'\n";
    scriptFile.close();

    system("gnuplot plot_script.gp");

    for(int i = 0; i < 25; i++){
        delete[] points[i];
    }
    delete[] points;
    
   
    return 0;
}


int find_vector(int n, double* A, double* x){
    double buf, buf2;
    int num = 0;

    for(int i = 0; i < n - 1; i++){
        buf = 0;
        num = i;
        //Выбираем строку с максимальным первым элементом
        for(int j = i; j < n ; j++){
            if(A[j * n + i] * A[j * n + i] > buf){
                buf = A[j * n + i] * A[j * n + i];
                num = j; 
            }
        }

        //Переносим эту строку наверх
        for(int j = i; j < n ; j++){
            buf = A[num * n + j];
            A[num * n + j] = A[i * n + j];
            A[i * n + j] = buf;
        }

        //Вычитаем строку из нижеследующих
        buf = A[i * n + i];
        for(int j = i + 1; j < n; j++){
            buf2 = A[j * n + i] / buf;
            for(int k = i; k < n; k++){
                A[j* n + k] -= A[i * n + k] * buf2;
            }
        }
    }

    x[n - 1] = 1;
    for(int i = n - 2; i >= 0; i--){
        x[i] = 0;
        for(int j = n - 1; j > i; j--){
            x[i] -= x[j] * A[i * n + j];
        }
        x[i] = x[i] / A[i * n + i];
    }

    buf = 0;

    for(int i = 0; i < n; i++){
        buf += x[i] * x[i];
    }
    buf2 = sqrt(buf);
    for(int i = 0; i < n; i++){
        x[i] /= buf2;
    }

    return 0;
}