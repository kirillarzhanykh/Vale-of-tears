
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include "solver.h"

// Главная функция
int main(int argc, char* argv[]) {

    double T = 1.0;
    int n = 100000;
    double h = T/(n-1);
    double alpha_values[] = { 0.0, 0.01, 0.5, 5.0, 10.5};
    int num_alpha = sizeof(alpha_values) / sizeof(alpha_values[0]);

    double* x1 = new double[n];
    double* x2 = new double[n];
    double* p1 = new double[n];
    double* p2 = new double[n];
    double* u = new double[n];


    // Создаем папку для решений, если она не существует
    system("mkdir -p solutions");

    for (int idx = 0; idx < num_alpha; ++idx) {
        double alpha = alpha_values[idx];

        double ab[2]; // a и b
        solve_ab(n, alpha, ab, x1, x2, p1, p2, h, u);

        // Запись данных в текстовый файл
        std::ostringstream filename_stream;
        filename_stream << "solutions/alpha" << idx << ".txt";
        std::cout<< std::setprecision(10);
        std::cout << "alpha=" << alpha
                  << " x1(0)=" << x1[0]
                  << " x2(0)=" << x2[0]
                  << " p1(0)=" << p1[0]
                  << " p2(0)=" << p2[0]
                  << std::endl;
        std::cout << "Решение для alpha = " << alpha << " и h = " << h << " записано в файл " << filename_stream.str() << std::endl;
        std::string filename = filename_stream.str();
        std::ofstream outfile(filename);
        if (outfile.is_open()) {
            
            outfile << std::scientific << std::setprecision(10);
            for (int i = 0; i < n; ++i) {
                double t = i * h;
                outfile << t << " " << x1[i] << " " << x2[i] << " " << p1[i] << " " << p2[i] << " " << u[i] << std::endl;
            }
            outfile.close();
        }
        else {
            std::cerr << "Не удалось открыть файл " << filename << " для записи." << std::endl;
        }
    }

    delete[] x1;
    delete[] x2;
    delete[] p1;
    delete[] p2;
    delete[] u;

    return 0;
}
