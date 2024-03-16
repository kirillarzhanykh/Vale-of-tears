/* Построить интерполяцию кубическими сплайнами Эрмита для функции 
exp(x) / (2x) + x^5 Log(x) , 
( её производная равна exp(x) * (x - 1) / (2x^2) + x^4 (5 Log(x) + 1) )
четвертая производная: (12 E^x)/x^5 - (12 E^x)/x^4 + (6 E^x)/x^3 - (2 E^x)/x^2 + E^x/(2 x) + 154 x + 120 x Log[x]
проходящую через точки с координатами 
x = {1, 2, 3, 4, 5} , 
найти максимальное отклонение интерполяции от этой функции 
на отрезке [ 1, 5] 
и сравнить его со значением верхней оценки для соответствующего метода интерполяции.

*/

#include <fstream>
#include <iostream>
#include <cmath>
#include "solver_H.h"

double max_dev(double left_a, double right_b, double p0, double p1, double p2, double p3, double eps);

int main(void){
    double x;
    double** points_values_derivatives;
    points_values_derivatives = new double *[5]; //5 точек

    for(int i = 0; i < 5; i++){
        points_values_derivatives[i] = new double [3];
        x = i + 1;
        points_values_derivatives[i][0] = x;
        points_values_derivatives[i][1] = exp(x) / (2 * x) + pow(x, 5) * log(x);
        points_values_derivatives[i][2] = exp(x) * (x - 1) / (2 * pow(x, 2)) + pow(x, 4) * (5 * log(x) + 1);
    }

    // Массив для поиска многочленов 
    double difference, segment;
    double** polynomials;
    polynomials = new double *[4]; //4 многочлена
    for(int i = 0; i < 4; i++){
        polynomials[i] = new double [4]; //4 коэффициента многолчена
       
        segment = points_values_derivatives[i + 1][0] - points_values_derivatives[i][0];
        difference = (points_values_derivatives[i + 1][1] - points_values_derivatives[i][1])/segment;
        polynomials[i][0] = points_values_derivatives[i][1];
        polynomials[i][1] = points_values_derivatives[i][2];
        polynomials[i][2] = (- 2 * points_values_derivatives[i][2] - points_values_derivatives[i + 1][2] + 3 * difference)/segment;
        polynomials[i][3] = (points_values_derivatives[i][2] + points_values_derivatives[i + 1][2] - 2 * difference)/(segment * segment);
        

    }

    std::ofstream dataFile("data.txt");
    for (int i = 0; i < 5; i++){
        dataFile << points_values_derivatives[i][0] << " " << points_values_derivatives[i][1] << "\n";
    
    }
    dataFile.close();

    std::ofstream scriptFile("plot_script.gp");
    scriptFile << "set terminal pngcairo enhanced color size 800,600\n";
    scriptFile << "set output 'interpolation_plot.png'\n";

    scriptFile << "x_1 = " <<  points_values_derivatives[0][0] << "\n";
    scriptFile << "a_1 = " <<  polynomials[0][0] << "\n";
    scriptFile << "b_1 = " <<  polynomials[0][1] << "\n";
    scriptFile << "c_1 = " <<  polynomials[0][2] << "\n";
    scriptFile << "d_1 = " <<  polynomials[0][3] << "\n";
    scriptFile << "p_1(x) = a_1 + b_1 * (x - x_1) + c_1 * (x - x_1)**2 + d_1 * (x - x_1)**3\n";

    scriptFile << "x_2 = " <<  points_values_derivatives[1][0] << "\n";
    scriptFile << "a_2 = " <<  polynomials[1][0] << "\n";
    scriptFile << "b_2 = " <<  polynomials[1][1] << "\n";
    scriptFile << "c_2 = " <<  polynomials[1][2] << "\n";
    scriptFile << "d_2 = " <<  polynomials[1][3] << "\n";
    scriptFile << "p_2(x) = a_2 + b_2 * (x - x_2) + c_2 * (x - x_2)**2 + d_2 * (x - x_2)**3\n";

    scriptFile << "x_3 = " <<  points_values_derivatives[2][0] << "\n";
    scriptFile << "a_3 = " <<  polynomials[2][0] << "\n";
    scriptFile << "b_3 = " <<  polynomials[2][1] << "\n";
    scriptFile << "c_3 = " <<  polynomials[2][2] << "\n";
    scriptFile << "d_3 = " <<  polynomials[2][3] << "\n";
    scriptFile << "p_3(x) = a_3 + b_3 * (x - x_3) + c_3 * (x - x_3)**2 + d_3 * (x - x_3)**3\n";

    scriptFile << "x_4 = " <<  points_values_derivatives[3][0] << "\n";
    scriptFile << "a_4 = " <<  polynomials[3][0] << "\n";
    scriptFile << "b_4 = " <<  polynomials[3][1] << "\n";
    scriptFile << "c_4 = " <<  polynomials[3][2] << "\n";
    scriptFile << "d_4 = " <<  polynomials[3][3] << "\n";
    scriptFile << "p_4(x) = a_4 + b_4 * (x - x_4) + c_4 * (x - x_4)**2 + d_4 * (x - x_4)**3\n";

    scriptFile << "f(x) = exp(x) / (2 * x) + x**5 * log(x)\n";
    scriptFile << "set xlabel 'x'\n";
    scriptFile << "set ylabel 'y'\n";
    scriptFile << "set grid\n";
    scriptFile << "set xrange[1 : 5]\n";
    scriptFile << "set yrange[f(1) : f(5)]\n";
    scriptFile << "set title 'Интерполяция сплайнами Эрмита'\n";
    scriptFile << "plot f(x) lw 4 lc rgb 'green',\
                        p_1(x) lw 2 lc rgb 'red',\
                        p_2(x) lw 2 lc rgb 'blue',\
                        p_3(x) lw 2 lc rgb 'yellow',\
                        p_4(x) lw 2 lc rgb 'black',\
                        'data.txt' using 1:2 with points title 'key points' lc rgb 'black'\n";
    scriptFile.close();

    system("gnuplot plot_script.gp");

    x = 5;
    double max_value = exp(x)*(12/pow(x, 5) - 12/pow(x, 4) + 6/pow(x, 3) - 2/pow(x, 2) + 1/(2 * x)) + 154 * x + 120 * x * log(x);
    double max_deviation = max_value / (4*3*2*2*2*2*2);
    double real_max_deviation = 0;
    for(int i = 0; i < 4; i++){
        x = max_dev(points_values_derivatives[i][0], points_values_derivatives[i + 1][0], polynomials[i][0], polynomials[i][1], polynomials[i][2], polynomials[i][3], 0.00001);
        if(x > real_max_deviation) real_max_deviation = x;
    }
    std::cout << "Оценка максимального отклонения: " << max_deviation <<std::endl;
    std::cout << "Реальное отклонение: " << real_max_deviation <<std::endl;
 
    for(int k = 0; k < 4; k++){
        delete[] polynomials[k];
    }
    delete[] polynomials;

    for(int i = 0; i < 5; i++){
        delete[] points_values_derivatives[i];
    }
    delete[] points_values_derivatives;

    return 0;

}


double max_dev(double left_a, double right_b, double p0, double p1, double p2, double p3, double eps){
    double phi = (3 - sqrt(5)) / 2;
    double a = left_a;
    double b = right_b;
    double x1 = a + phi * (b - a);
    double x2 = b - phi * (b - a);
    double y1, y2;
    

    for(int i = 0; i < 1000; i++){
        y1 = fabs((exp(x1) / (2 * x1) + pow(x1, 5) * log(x1)) - (p0 + p1 * (x1 - left_a) + p2 * pow((x1 - left_a), 2) + p3 * pow((x1 - left_a), 3)));
        y2 = fabs((exp(x2) / (2 * x2) + pow(x2, 5) * log(x2)) - (p0 + p1 * (x2 - left_a) + p2 * pow((x2 - left_a), 2) + p3 * pow((x2 - left_a), 3)));
        if(y1 > y2){
            b = x2;
            x2 = x1;
            x1 = a + phi * (b - a);
        } else {
            a = x1;
            x1 = x2;
            x2 = b - phi * (b - a);
        }
        if(fabs(a - b) < eps){
            x1 = (a + b) / 2;
            y1 = fabs((exp(x1) / (2 * x1) + pow(x1, 5) * log(x1)) - (p0 + p1 * (x1 - left_a) + p2 * pow((x1 - left_a), 2) + p3 * pow((x1 - left_a), 3)));
            return y1;
        }
    }
    x1 = (a + b) / 2;
    y1 = fabs((exp(x1) / (2 * x1) + pow(x1, 5) * log(x1)) - (p0 + p1 * (x1 - left_a) + p2 * pow((x1 - left_a), 2) + p3 * pow((x1 - left_a), 3)));
    return y1;
}